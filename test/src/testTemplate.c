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

#define TEMPLATE_GROUP_NODE DT_NODELABEL( mw_templates )
#define TEMPLATE_CNT        DT_PROP_LEN( TEMPLATE_GROUP_NODE, mw_templates )
#define TEMPLATE_NODE( i )  DT_PHANDLE_BY_IDX( TEMPLATE_GROUP_NODE, mw_templates, i )

#define TEMPLATE_LABEL_GET( n, _ ) DT_PROP( TEMPLATE_NODE( n ), label ),
#define TEMPLATE_VALUE_GET( n, _ ) DT_PROP( TEMPLATE_NODE( n ), value ),

/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
static uint32_t getVal;
static bool zbusCbFired = false;

// grab individual button settings from the overlay config
static const uint32_t templateValues[] = { LISTIFY( TEMPLATE_CNT, TEMPLATE_VALUE_GET, () ) };

/**** Prototypes ******************************************************************************************************/
static void *testSetup( void );
static void testTeardown( void * );
static void zbusListenerCb( const struct zbus_channel *chan );
static int zbusListenerCbWait();

/**** Macros **********************************************************************************************************/

LOG_MODULE_REGISTER( test_module, LOG_LEVEL_DBG );

ZBUS_LISTENER_DEFINE( template_test_lis, zbusListenerCb );
ZBUS_CHAN_ADD_OBS( ZBUS_CHAN_TEMPLATE_VAL_SUB, template_test_lis, 0 );

/**** Definitions *****************************************************************************************************/

static void *testSetup( void )
{
    // Give the template driver time to init
    k_sleep( K_MSEC( 1000 ) );

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

int zbusListenerCbWait()
{
    int16_t timeout = 1000;

    while( !zbusCbFired && timeout ) {
        k_sleep( K_MSEC( 1 ) );
        if( --timeout <= 0 ) {
            return 1;
        }
    }
    zbusCbFired = false;
    return 0;
}

ZTEST( test_template, test_template_hdr_init_val )
{
    templateInit();

    for( int i = 0; i < TEMPLATE_CNT; i++ ) {
        templateValRead( i, &getVal );
        zassert_equal( getVal, templateValues[i], "Test hrd init val [ set:%d | get:%d ]", templateValues[i], getVal );
    }
}

ZTEST( test_template, test_template_hdr_read_write_val )
{
    for( int i = 0; i < TEMPLATE_CNT; i++ ) {
        for( uint16_t setVal = 0; setVal < UINT16_MAX; setVal++ ) {
            templateValWrite( i, setVal );
            templateValRead( i, &getVal );
            zassert_equal( getVal, setVal, "Test hrd write/read val [ set:%d | get:%d ]", setVal, getVal );
        }
    }
}

ZTEST( test_template, test_template_zbus_init_val )
{
    templateInit();

    for( int i = 0; i < TEMPLATE_CNT; i++ ) {
        ZbusMsgTemplate zbusMsg = { 0 };
        zbusMsg.type = i;

        zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ, &zbusMsg, K_NO_WAIT );
        zbusListenerCbWait();

        zassert_equal( getVal, templateValues[i], "Test hrd init val [ set:%d | get:%d ]", templateValues[i], getVal );
    }
}

ZTEST( test_template, test_template_zbus_read_write_val )
{
    ZbusMsgTemplate zbusMsg = { 0 };
    for( int i = 0; i < TEMPLATE_CNT; i++ ) {
        for( uint8_t setVal = 0; setVal < UINT8_MAX; setVal++ ) {
            uint8_t setVal = i;
            zbusMsg.val = setVal;
            zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_SET, &zbusMsg, K_NO_WAIT );
            zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ, &zbusMsg, K_NO_WAIT );
            zbusListenerCbWait();
            zassert_equal( getVal, setVal, "Test zbus write/read val [ set:%d | get:%d ]", setVal, getVal );
        }
    }
}

ZTEST_SUITE( test_template, NULL, testSetup, NULL, testTeardown, NULL );