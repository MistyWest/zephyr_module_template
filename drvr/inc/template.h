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
/**** Variables *******************************************************************************************************/
/**** Macros **********************************************************************************************************/
/**** Prototypes ******************************************************************************************************/

/**
 * @brief Init the module
 *
 * @return int
 */
ErrCode templateInit( void );

/**
 * @brief Read Module Val
 *
 * @return ErrCode
 */
ErrCode templateValRead( uint16_t *val );

/**
 * @brief Write Module Val
 *
 * @param val
 * @return ErrCode
 */
ErrCode templateValWrite( uint16_t val );

/**
 * @brief Publish Module Val
 *
 * @return ErrCode
 */
ErrCode templateValZbusPublish( void );