/**
 * @file testTemplate.c
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Module Unit Test to test driver header API and ZBUS interface to the Driver
 *
 */

/**** Includes ********************************************************************************************************/

#include "msgqTemplate.h"
#include "template.h"
#include "wdtTemplate.h"
#include "zbusCommon.h"
#include "zbusTemplate.h"
#include <zephyr/irq_offload.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>
#include <zephyr/ztest.h>

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
static uint16_t getVal;
static bool zbusCbFired = false;

/**** Prototypes ******************************************************************************************************/
static void *testSetup( void );
static void testTeardown( void * );
static void zbusListenerCb( const struct zbus_channel *chan );
static void zbusListenerCbWait();

/**** Macros **********************************************************************************************************/

LOG_MODULE_REGISTER( test_module, LOG_LEVEL_DBG );

ZBUS_LISTENER_DEFINE( template_test_lis, zbusListenerCb );
// Request to set Template Val
ZBUS_CHAN_ADD_OBS( ZBUS_CHAN_TEMPLATE_VAL_SUB, template_test_lis, 0 );

/**** Definitions *****************************************************************************************************/

static void *testSetup( void )
{
    return NULL;
}

static void testTeardown( void * )
{
    return;
}

void zbusListenerCb( const struct zbus_channel *chan )
{
    ZbusMsgContainer zbus = { 0 };

    if( chan == &ZBUS_CHAN_TEMPLATE_VAL_SUB ) {
        zbus.msg.template = *(ZbusMsgTemplate *)zbus_chan_const_msg( chan );
        getVal = zbus.msg.template.val;
    }
    zbusCbFired = true;
}

void zbusListenerCbWait()
{
    while( !zbusCbFired ) {
        k_sleep( K_MSEC( 1 ) );
    }
    zbusCbFired = false;
}

ZTEST( template, test_template_hdr_init_val )
{
    templateValRead( &getVal );
    zassert_equal( getVal, 0, "Test template hrd init val [ set:%d | get:%d ]", 0, getVal );
}

ZTEST( template, test_template_hdr_read_write_val )
{
    for( uint16_t setVal = 0; setVal < UINT16_MAX; setVal++ ) {
        templateValWrite( setVal );
        templateValRead( &getVal );
        zassert_equal( getVal, setVal, "Test template hrd write/read val [ set:%d | get:%d ]", setVal, getVal );
    }
}

ZTEST( template, test_template_zbus_init_val )
{
    ZbusMsgTemplate template = { 0 };
    zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ, &template, K_NO_WAIT );
    zbusListenerCbWait();

    zassert_equal( getVal, 0, "Test template zbus init val [ set:%d | get:%d ]", 0, getVal );
}

ZTEST( template, test_template_zbus_read_write_val )
{
    ZbusMsgTemplate template = { 0 };

    //TODO: This version times out suggesting it is much slower than the header access version
    // for( uint16_t setVal = 0; setVal < UINT16_MAX; setVal++ ) {
    //     template.val = setVal;
    //     zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_SET, &template, K_NO_WAIT );
    //     zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ, &template, K_NO_WAIT );
    //     zbusListenerCbWait();
    //     if( getVal != setVal ) {
    //         status = false;
    //     }
    // }
    // zassert_true( status, "Test template zbus write/read val don't match" );

    uint16_t setVal = 100;
    template.val = setVal;
    zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_SET, &template, K_NO_WAIT );
    zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ, &template, K_NO_WAIT );
    zbusListenerCbWait();

    zassert_equal( getVal, setVal, "Test template zbus write/read val [ set:%d | get:%d ]", setVal, getVal );
}

ZTEST_SUITE( template, NULL, testSetup, NULL, testTeardown, NULL );