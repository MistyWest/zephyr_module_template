/**
 * @file template.c
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Module Common
 *
 */

/**** Includes ********************************************************************************************************/
#include "template.h"
#include "msgqTemplate.h"
#include "zbusCommon.h"
#include <errno.h>
#include <zephyr/logging/log.h>

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
static uint16_t templateVal;

/**** Macros **********************************************************************************************************/
LOG_MODULE_DECLARE( template_main, CONFIG_APP_TEMPLATE_LOG_LEVEL );

/**** Prototypes ******************************************************************************************************/
/**** Definitions *****************************************************************************************************/

int templateInit()
{
    int ret = ERR_OK;

    templateVal = 0;

    return ret;
}

int templateValRead( uint16_t *val )
{
    int ret = ERR_OK;

    *val = templateVal;

    return ret;
}

int templateValWrite( uint16_t val )
{
    int ret = ERR_OK;

    templateVal = val;

    return ret;
}

int templateValZbusPublish( void )
{
    int ret = ERR_OK;
    ZbusMsgTemplate templateMsg = { 0 };

    ret = templateValRead( &templateMsg.val );
    if( ret < ERR_OK ) {
        LOG_ERR( "Failed to read val: %d\n", ret );
        return ret;
    }

    ret = zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_SUB, &templateMsg, K_NO_WAIT );
    if( ret < ERR_OK ) {
        LOG_ERR( "Failed to publish val: %d\n", ret );
        return ret;
    }

    return ret;
}