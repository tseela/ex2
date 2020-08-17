#include <iostream>
#include <exception>
#include "ErrorCode.h"

class MatrixException : public std::exception {
    ErrorCode m_errorCode;

    public:
        MatrixException(ErrorCode errorCode) {
            m_errorCode = errorCode;
        }

        std::string getExceptionMessage() {
            return error_getErrorMessage(m_errorCode);
        }
};