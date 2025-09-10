/**
 * @file mainTemplate.c
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Main entry point
 *
 */

/**** Includes ********************************************************************************************************/
#include "error.h"
#include "msgqTemplate.h"
#include "template.h"
#include "wdtTemplate.h"
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
/**** Macros **********************************************************************************************************/

LOG_MODULE_REGISTER( template_main, CONFIG_APP_TEMPLATE_LOG_LEVEL );

/**** Prototypes ******************************************************************************************************/

/**
 * @brief Module Thread
 *
 */
static void templateMain( void );

/**** Definitions *****************************************************************************************************/

static void templateMain( void )
{
    int ret = ERR_OK;

    LOG_DBG( "Module Thread started" );

    ret = templateInit();
    if( ret != ERR_OK ) {
        LOG_ERR( "Failed to init module: %d", ret );
        return;
    }

    ret = wdtTemplateInit();
    if( ret != ERR_OK ) {
        LOG_ERR( "Failed to init time thread WDT: %d", ret );
        return;
    }

    while( true ) {
        ret = wdtTemplateFeed();
        if( ret < ERR_OK ) {
            LOG_ERR( "Failed to feed the watchdog: %d", ret );
            return;
        }

        ret = msgqTemplateProc();
        if( ret < ERR_OK ) {
            LOG_ERR( "Failed to process template msgq: %d", ret );
        }
    }
}

/***************************************************************************************/

K_THREAD_DEFINE( template_main_id, CONFIG_APP_TEMPLATE_STACK_SIZE, templateMain, NULL, NULL, NULL, CONFIG_APP_TEMPLATE_PRIORITY, 0,
                 CONFIG_APP_TEMPLATE_DELAY_START_MS );