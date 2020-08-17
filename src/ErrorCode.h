#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif 

typedef enum {
    // No error
    ERROR_SUCCESS = 0,
    // malloc faild
    ERROR_MEMORY = 1,
    // the user gave the function a NULL pointer
    ERROR_NULL = 2,
    // the user tries to approach a row or a col that doesn't exists
    ERROR_ROW_COL = 3,
    // the user tries to add two matrixes from different sizes
    ERROR_ADD_SIZES = 4,
    // the user tries to multiply two matrixes that can't be multiplied
    ERROR_MULT_SIZES = 5,
    // matrix's width or height can't be 0
    ERROR_ZERO_SIZE = 6
} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code);

#ifdef __cplusplus
}
#endif