/**
 * @file msgqTemplate.c
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Task Message Queue Module
 *
 */

/**** Includes ********************************************************************************************************/
#include "msgqTemplate.h"
#include "error.h"
#include "template.h"
#include <zephyr/logging/log.h>

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
/**** Macros **********************************************************************************************************/

LOG_MODULE_DECLARE( template_main, CONFIG_APP_TEMPLATE_LOG_LEVEL );

// Define the internal message queue
K_MSGQ_DEFINE( MsgqTemplate, sizeof( MsgqTemplateMsgContainer ), CONFIG_APP_TEMPLATE_MSGQ_SIZE, CONFIG_APP_TEMPLATE_MSGQ_ALIGN );

/**** Prototypes ******************************************************************************************************/
/**** Definitions *****************************************************************************************************/

struct k_msgq *msgqTemplate( void )
{
    return &MsgqTemplate;
}

int msgqTemplateProc( void )
{
    int ret = ERR_OK;
    MsgqTemplateMsgContainer msgq = { 0 };
    const k_timeout_t msgQueWaitMs = K_MSEC( MSEC_PER_SEC * CONFIG_APP_TEMPLATE_MSGQ_TIMEOUT_S );

    // we timeout every second to feed the task wdt
    ret = k_msgq_get( msgqTemplate(), &msgq, msgQueWaitMs );
    if( ret == -EAGAIN ) {
        return ERR_OK;
    }

    // Here we have a valid message to process
    switch( msgq.type ) {
    case MSGQ_TYPE_ZBUS_TEMPLATE_VAL_SET:
        ret = templateValWrite( msgq.msg.zbus.msg.template.type, msgq.msg.zbus.msg.template.val );
        if( ret != ERR_OK ) {
            LOG_ERR( "Error Setting Template Val received from Zbus" );
        }
        break;
    case MSGQ_TYPE_ZBUS_TEMPLATE_VAL_PUB:
        ret = templateValZbusPublish( msgq.msg.zbus.msg.template.type );
        if( ret != ERR_OK ) {
            LOG_ERR( "Error Publishing Template Val to Zbus" );
        }
        break;
    default:
        LOG_ERR( "Unknown message type: %d", msgq.type );
        break;
    }

    return ret;
}