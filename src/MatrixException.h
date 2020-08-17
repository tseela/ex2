#pragma once
#ifndef _MATRIXEXCEPTION_H
#define _MATRIXEXCEPTION_H

#include <exception>
#include "ErrorCode.h"

class MatrixException : public std::exception {
    public:
        /**
         * @brief Construct a new Matrix Exception object.
         * 
         * @param errorCode 
         */
        MatrixException(ErrorCode errorCode);

        /**
         * @brief Gives an error message for the exception.
         * 
         * @return const char* - The error message.
         */
        const char* what();

    private:
        ErrorCode m_errorCode;
};

#endif
