/**
 * @file template.h
 * @date 20250526
 * @author flynnty
 * @copyright flynnty 2025
 *
 * @brief
 * Module
 *
 */
#pragma once

/**** Includes ********************************************************************************************************/
#include "error.h"
#include <stdint.h>

/**** Defines *********************************************************************************************************/
/**** Types ***********************************************************************************************************/

// Exposing button configuration type so we can access it from local module unit tests
typedef struct
{
    uint32_t value;
    const char *label;
} template_t;

/**** Variables *******************************************************************************************************/
/**** Macros **********************************************************************************************************/
/**** Prototypes ******************************************************************************************************/

/**
 * @brief Init the module
 *
 * @return int
 */
int templateInit( void );

/**
 * @brief Read Module Val
 *
 * @return int
 */
int templateValRead( uint32_t idx, uint32_t *val );

/**
 * @brief Write Module Val
 *
 * @param val
 * @return int
 */
int templateValWrite( uint32_t idx, uint32_t val );

/**
 * @brief Publish Module Val
 *
 * @return int
 */
int templateValZbusPublish( uint32_t idx );