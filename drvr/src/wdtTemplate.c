/**
 * @file wdtTemplate.c
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Task Watch Dog Timer Module
 *
 */

/**** Includes ********************************************************************************************************/
#include "wdtTemplate.h"
#include <zephyr/logging/log.h>
#include <zephyr/task_wdt/task_wdt.h>

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
static int wdtTaskId = -1;
static const uint32_t wdtTimeoutMs = ( CONFIG_APP_TEMPLATE_WDT_TIMEOUT_S * MSEC_PER_SEC );

/**** Macros **********************************************************************************************************/
LOG_MODULE_DECLARE( template_main, CONFIG_APP_TEMPLATE_LOG_LEVEL );

BUILD_ASSERT( CONFIG_APP_TEMPLATE_WDT_TIMEOUT_S > CONFIG_APP_TEMPLATE_MSGQ_TIMEOUT_S, "Watchdog timeout must be greater than trigger timeout" );

/**** Prototypes ******************************************************************************************************/

/**
 * @brief Time WDT timeout callback
 *
 * @param channel_id
 * @param user_data
 */
static void wdtTimeoutCb( int chanId, void *userData );

/**** Definitions *****************************************************************************************************/

void wdtTimeoutCb( int chanId, void *userData )
{
    LOG_ERR( "Watchdog expired, Channel: %d, Thread: %s", chanId, k_thread_name_get( (k_tid_t)userData ) );
}

ErrCode wdtTemplateInit()
{
    int ret = ERR_OK;

    ret = task_wdt_add( wdtTimeoutMs, wdtTimeoutCb, (void *)k_current_get() );
    if( ret < ERR_OK ) {
        LOG_ERR( "Failed to add task to watchdog: %d", wdtTaskId );
        return ret;
    }
    wdtTaskId = ret;

    return ERR_OK;
}

ErrCode wdtTemplateFeed()
{
    int ret = ERR_OK;

    ret = task_wdt_feed( wdtTaskId );
    if( ret < ERR_OK ) {
        LOG_ERR( "Failed to feed the watchdog: %d", ret );
        return ret;
    }
    return ret;
}
