/**
 * @file zbusTemplate.c
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Task Zbus Module
 *
 */

/**** Includes ********************************************************************************************************/
#include "zbusTemplate.h"

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
/**** Macros **********************************************************************************************************/
/**** Prototypes ******************************************************************************************************/
/**** Definitions *****************************************************************************************************/

/**
 * @file zbusTemplate.c
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Module Zbus
 *
 */

/**** Includes ********************************************************************************************************/
#include "error.h"
#include "msgqTemplate.h"
#include "template.h"
#include "zbusCommon.h"
#include <zephyr/logging/log.h>

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
/**** Prototypes ******************************************************************************************************/
static void zbusListenerCb( const struct zbus_channel *chan );

/**** Macros **********************************************************************************************************/
LOG_MODULE_DECLARE( template_main, CONFIG_APP_TEMPLATE_LOG_LEVEL );

ZBUS_LISTENER_DEFINE( template_thread_lis, zbusListenerCb );
ZBUS_CHAN_ADD_OBS( ZBUS_CHAN_TEMPLATE_VAL_SET, template_thread_lis, 0 );
ZBUS_CHAN_ADD_OBS( ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ, template_thread_lis, 0 );

/**** Definitions *****************************************************************************************************/

void zbusListenerCb( const struct zbus_channel *chan )
{
    MsgqTemplateMsgContainer msgq = { 0 };
    int ret = ERR_OK;

    if( chan == &ZBUS_CHAN_TEMPLATE_VAL_SET ) {
        msgq.type = MSGQ_TYPE_ZBUS_TEMPLATE_VAL_SET;
        msgq.msg.zbus.type = ZBUS_TYPE_TEMPLATE_VAL_SET;
        msgq.msg.zbus.msg.template = *(ZbusMsgTemplate *)zbus_chan_const_msg( chan );
        ret = k_msgq_put( msgqTemplate(), &msgq, K_NO_WAIT );
    } else if( chan == &ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ ) {
        msgq.type = MSGQ_TYPE_ZBUS_TEMPLATE_VAL_PUB;
        msgq.msg.zbus.msg.template = *(ZbusMsgTemplate *)zbus_chan_const_msg( chan );
        ret = k_msgq_put( msgqTemplate(), &msgq, K_NO_WAIT );
    }

    if( ret != ERR_OK ) {
        LOG_ERR( "ERR: Event queue full, dropping Zbus message" );
    }
}
