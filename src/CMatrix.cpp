#include "CMatrix.h"
#include "Matrix.h"
#include "ErrorCode.h"
#include <iostream>
#include <exception>


CMatrix::CMatrix(uint32_t height, uint32_t width) {
    if (!error_isSuccess(matrix_create(&m_matrix, height, width)))
       throw new MatrixException(matrix_create(&m_matrix, height, width));
}

CMatrix::CMatrix(const PMatrix& m) {
    if (!error_isSuccess(matrix_copy(&m_matrix, m)))
        throw new MatrixException(matrix_copy(&m_matrix, m));
}

CMatrix::CMatrix(const CMatrix& m) {
    if (!error_isSuccess(matrix_copy(&m_matrix, m.m_matrix)))
        throw new MatrixException(matrix_copy(&m_matrix, m.m_matrix));
}
        
CMatrix& CMatrix::operator=(const CMatrix& other) {
    if (!error_isSuccess(matrix_copy(&m_matrix, other.m_matrix)))
        throw new MatrixException(matrix_copy(&m_matrix, other.m_matrix));
    return *this;
}

CMatrix::CMatrix(CMatrix&& m) noexcept {
    m_matrix = m.m_matrix;
}

CMatrix& CMatrix::operator=(CMatrix&& m) noexcept {
    return *this;
}

CMatrix::~CMatrix() {
    matrix_destroy(m_matrix);
}


uint32_t CMatrix::getHeight() const {
    uint32_t height;
    if (!error_isSuccess(matrix_getHeight(m_matrix, &height)))
        throw new MatrixException(matrix_getHeight(m_matrix, &height));
    return height;
}

uint32_t CMatrix::getWidth() const {
    uint32_t width;
    if (!error_isSuccess(matrix_getWidth(m_matrix, &width)))
        throw new MatrixException(matrix_getWidth(m_matrix, &width));
    return width;
}

void CMatrix::setValue(uint32_t rowIndex, uint32_t colIndex, double value) {
    if (!error_isSuccess(matrix_setValue(m_matrix, rowIndex, colIndex, value)))
        throw new MatrixException(matrix_setValue(m_matrix, rowIndex, colIndex, value));
}

void CMatrix::multMatrixWithScalar(double scalar) {
    if (!error_isSuccess(matrix_multiplyWithScalar(m_matrix, scalar)))
        throw new MatrixException(matrix_multiplyWithScalar(m_matrix, scalar));
}



/**
 * 
 * We need to change this functions.
 * Maybe copy our impliment and change the arguments type to pointers?
 * 
 */
CMatrix add(const CMatrix& lhs, const CMatrix& rhs) {
    PMatrix m;
    ErrorCode ec = matrix_add(&m, lhs.m_matrix, rhs.m_matrix);
    if (!error_isSuccess(ec))
        throw new MatrixException(ec);
    return new CMatrix(m);
}

CMatrix multMatrix(const CMatrix& lhs, const CMatrix& rhs) {
    PMatrix m;
    ErrorCode ec = matrix_multiplyMatrices(&m, lhs.m_matrix, rhs.m_matrix);
    if (!error_isSuccess(ec))
        throw new MatrixException(ec);
    return new CMatrix(m);
}