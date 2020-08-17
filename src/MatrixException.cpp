include "MatrixException.h"
#include "ErrorCode.h"
#include <iostream>
#include <exception>


MatrixException::MatrixException(ErrorCode errorCode) {
    m_errorCode = errorCode;
}

const char* MatrixException::what() const {
    return error_getErrorMessage(m_errorCode);
}

