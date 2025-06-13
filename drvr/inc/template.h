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
enum ErrCode_e templateInit( void );

/**
 * @brief Read Module Val
 *
 * @return ErrCode
 */
enum ErrCode_e templateValRead( uint16_t *val );

/**
 * @brief Write Module Val
 *
 * @param val
 * @return ErrCode
 */
enum ErrCode_e templateValWrite( uint16_t val );

/**
 * @brief Publish Module Val
 *
 * @return ErrCode
 */
enum ErrCode_e templateValZbusPublish( void );