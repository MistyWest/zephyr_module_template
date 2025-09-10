/**
 * @file shellTemplate.c
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Module Shell for access to the driver from the Zephyr Shell
 *
 * @details
 * The shell should only ever interact with the driver through the zbus and not the headers.  This serves
 * as a real world test interface and an example for how to interact with the driver through the Zbus interface
 *
 */

/**** Includes ********************************************************************************************************/
#include "zbusCommon.h"
#include <stdio.h>
#include <stdlib.h>
#include <zephyr/shell/shell.h>

/**** Defines *********************************************************************************************************/
#define TEMPLATE_GROUP_NODE DT_NODELABEL( values )
#define TEMPLATE_CNT        DT_PROP_LEN( TEMPLATE_GROUP_NODE, values )

/**** Types ***********************************************************************************************************/
/**** Variables *******************************************************************************************************/
static const struct shell *shell_context;
static uint16_t getVal = 0;
static bool zbusCbFired = false;

/**** Prototypes ******************************************************************************************************/
static void zbusListenerCb( const struct zbus_channel *chan );
static int zbusListenerCbWait();
static int shellTemplateValRead( const struct shell *shell, size_t argc, char **argv );
static int shellTemplateValWrite( const struct shell *shell, size_t argc, char **argv );
static int shellTemplateTest( const struct shell *shell, size_t argc, char **argv );

/**** Macros **********************************************************************************************************/

ZBUS_LISTENER_DEFINE( template_shell_lis, zbusListenerCb );
// Request to set Template Val
ZBUS_CHAN_ADD_OBS( ZBUS_CHAN_TEMPLATE_VAL_SUB, template_shell_lis, 0 );

/**** Definitions *****************************************************************************************************/

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

static int shellTemplateValRead( const struct shell *shell, size_t argc, char **argv )
{
    shell_context = shell;

    if( argc < 2 ) {
        shell_error( shell, "Usage: get <idx>" );
        return -EINVAL;
    }

    errno = 0;
    char *endptr;
    uint32_t idx = (uint16_t)strtoul( argv[1], &endptr, 10 );

    if( errno != 0 || *endptr != '\0' ) {
        shell_error( shell, "Invalid idx: %s", argv[1] );
        return -EINVAL;
    }

    ZbusMsgTemplate zbusMsg = { 0 };
    zbusMsg.type = idx;

    zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ, &zbusMsg, K_NO_WAIT );
    if( zbusListenerCbWait() ) {
        shell_print( shell_context, "Timeout, value not received\n" );

    } else {
        shell_print( shell_context, "template:%d, val:%d", idx, getVal );
    }

    return 0;
}

static int shellTemplateValWrite( const struct shell *shell, size_t argc, char **argv )
{
    shell_context = shell;

    if( argc < 3 ) {
        shell_error( shell, "Usage: set <idx> <val>" );
        return -EINVAL;
    }

    errno = 0;
    char *endptr;
    uint32_t idx = (uint16_t)strtoul( argv[1], &endptr, 10 );

    if( errno != 0 || *endptr != '\0' ) {
        shell_error( shell, "Invalid idx: %s", argv[1] );
        return -EINVAL;
    }

    uint32_t val = (uint16_t)strtoul( argv[2], &endptr, 10 );

    if( errno != 0 || *endptr != '\0' ) {
        shell_error( shell, "Invalid val: %s", argv[2] );
        return -EINVAL;
    }

    ZbusMsgTemplate zbusMsg = { 0 };
    zbusMsg.val = val;
    zbusMsg.type = idx;
    zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_SET, &zbusMsg, K_NO_WAIT );

    return 0;
}

static int shellTemplateTest( const struct shell *shell, size_t argc, char **argv )
{
    shell_context = shell;
    bool status = true;
    ZbusMsgTemplate zbusMsg = { 0 };

    for( int i = 0; i < TEMPLATE_CNT; i++ ) {
        for( uint16_t setVal = 0; setVal < UINT16_MAX; setVal++ ) {
            zbusMsg.val = setVal;
            zbusMsg.type = i;
            zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_SET, &zbusMsg, K_NO_WAIT );
            zbus_chan_pub( &ZBUS_CHAN_TEMPLATE_VAL_PUB_REQ, &zbusMsg, K_NO_WAIT );
            zbusListenerCbWait();

            if( getVal != setVal ) {
                status = false;
                break;
            }
        }
    }

    shell_print( shell_context, "Test Template:%s", status ? "Pass" : "Fail" );

    return 0;
}

// clang-format off
SHELL_STATIC_SUBCMD_SET_CREATE( sub_list,
    SHELL_CMD( read, NULL, "Read Value", shellTemplateValRead ),
    SHELL_CMD( write, NULL, "Write Value", shellTemplateValWrite ),
    SHELL_CMD( test, NULL, "Test Template", shellTemplateTest ),
    SHELL_SUBCMD_SET_END );
// clang-format on

SHELL_CMD_REGISTER( template, &sub_list, "Template Commands", NULL );