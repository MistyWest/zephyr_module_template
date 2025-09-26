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
#include <zephyr/sys/util.h>

/**** Defines *********************************************************************************************************/
#define TEMPLATE_GROUP_NODE DT_NODELABEL( mw_templates )
#define TEMPLATE_CNT        DT_PROP_LEN( TEMPLATE_GROUP_NODE, mw_templates )
#define TEMPLATE_NODE( i )  DT_PHANDLE_BY_IDX( TEMPLATE_GROUP_NODE, mw_templates, i )

#define TEMPLATE_LABEL_GET( n, _ ) DT_PROP( TEMPLATE_NODE( n ), label ),
#define TEMPLATE_VALUE_GET( n, _ ) DT_PROP( TEMPLATE_NODE( n ), value ),

/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
static template_t templates[TEMPLATE_CNT] = { 0 };

// grab individual button settings from the overlay config
static const char *templateLabels[] = { LISTIFY( TEMPLATE_CNT, TEMPLATE_LABEL_GET, () ) };
static const uint32_t templateValues[] = { LISTIFY( TEMPLATE_CNT, TEMPLATE_VALUE_GET, () ) };

/**** Macros **********************************************************************************************************/
LOG_MODULE_DECLARE( template_main, CONFIG_APP_TEMPLATE_LOG_LEVEL );

/**** Prototypes ******************************************************************************************************/
/**** Definitions *****************************************************************************************************/

int templateInit()
{
    int ret = ERR_OK;

    for( int i = 0; i < TEMPLATE_CNT; i++ ) {
        template_t *temp = &templates[i];
        temp->value = templateValues[i];
        temp->label = templateLabels[i];
        LOG_DBG( "Template(%d) %s init value %d", i, temp->label, temp->value );
    }

    return ret;
}

int templateValRead( uint32_t idx, uint32_t *val )
{
    int ret = ERR_OK;

    if( idx >= TEMPLATE_CNT ) {
        LOG_ERR( "Template index out of bounds" );
        return -1;
    }

    *val = templates[idx].value;

    return ret;
}

int templateValWrite( uint32_t idx, uint32_t val )
{
    int ret = ERR_OK;

    if( idx >= TEMPLATE_CNT ) {
        LOG_ERR( "Template index out of bounds" );
        return -1;
    }

    templates[idx].value = val;

    return ret;
}

int templateValZbusPublish( uint32_t idx )
{
    int ret = ERR_OK;
    ZbusMsgTemplate templateMsg = { 0 };
    templateMsg.type = idx;

    ret = templateValRead( idx, &templateMsg.val );
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