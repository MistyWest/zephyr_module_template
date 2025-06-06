/**
 * @file msgqTemplate.h
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Task Message Queue Module
 *
 */
#pragma once

/**** Includes ********************************************************************************************************/
#include "zbusCommon.h"

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/

typedef enum
{
    MSGQ_TYPE_ZBUS_TEMPLATE_VAL_SET = 0,
    MSGQ_TYPE_ZBUS_TEMPLATE_VAL_PUB,
    MSGQ_TYPE_COUNT
} MsgqTemplateMsgType;

typedef struct
{
    MsgqTemplateMsgType type;
    union
    {
        ZbusMsgContainer zbus;
    } msg;
} MsgqTemplateMsgContainer;

/**** Variables *******************************************************************************************************/
/**** Macros **********************************************************************************************************/
/**** Prototypes ******************************************************************************************************/

/**
 * @brief Get event msgq handle
 *
 * @return struct k_msgq*
 */
struct k_msgq *msgqTemplate( void );

/**
 * @brief Process Module Work Q
 *
 * @return int
 */
int msgqTemplateProc( void );
