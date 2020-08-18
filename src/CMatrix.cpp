#include "CMatrix.h"
#include "Matrix.h"
#include "ErrorCode.h"
#include <iostream>
#include <exception>

/**
 * @brief Construct a new CMatrix::CMatrix object
 * 
 * @param height the height of the matrix
 * @param width the width of the matrix
 */
CMatrix::CMatrix(uint32_t height, uint32_t width) { 
    if (!error_isSuccess(matrix_create(&m_matrix, height, width)))
       throw new MatrixException(matrix_create(&m_matrix, height, width));
}


CMatrix::CMatrix(const PMatrix& m) {
    if (!error_isSuccess(matrix_copy(&m_matrix, m)))
        throw new MatrixException(matrix_copy(&m_matrix, m));
}
/**
 * @brief Construct a new CMatrix::CMatrix object
 * copy ctor
 * @param m the other CMatrix to copy
 */
CMatrix::CMatrix(const CMatrix& m) {
    if (!error_isSuccess(matrix_copy(&m_matrix, m.m_matrix)))
        throw new MatrixException(matrix_copy(&m_matrix, m.m_matrix));
}
/**
 * @brief copy assignment operator
 * 
 * @param other 
 * @return CMatrix& 
 */
CMatrix& CMatrix::operator=(const CMatrix& other) {
    return *this;
}
/**
 * @brief Construct a new CMatrix::CMatrix object
 * move ctor
 * @param m 
 */
CMatrix::CMatrix(CMatrix&& m) noexcept {
    m_matrix = m.m_matrix;
}

/**
 * @brief move assignment operator
 * 
 * @param m 
 * @return CMatrix& 
 */
CMatrix& CMatrix::operator=(CMatrix&& m) noexcept {
    return *this;
}

/**
 * @brief Destroy the CMatrix::CMatrix object
 * 
 */
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

double CMatrix::getValue(uint32_t rowIndex, uint32_t colIndex) const {
    double value;
    if (!error_isSuccess(matrix_getValue(m_matrix, rowIndex, colIndex, &value)))
        throw new MatrixException(matrix_getValue(m_matrix, rowIndex, colIndex, &value));
    return value;
}

void CMatrix::multMatrixWithScalar(double scalar) {
    if (!error_isSuccess(matrix_multiplyWithScalar(m_matrix, scalar)))
        throw new MatrixException(matrix_multiplyWithScalar(m_matrix, scalar));
}




CMatrix add(const CMatrix& lhs, const CMatrix& rhs) {
    // if the sizes of the matrices does not match
    if (lhs.getHeight() != rhs.getHeight() || lhs.getWidth() != rhs.getWidth())
        throw new MatrixException(ERROR_ADD_SIZES);
    // creates the result matrix of adding the given ones
    CMatrix* matrix = new CMatrix::CMatrix(lhs.getHeight(), lhs.getWidth());
    // sets the values of the new matrix (adding lhs & rhs)
    for (uint32_t i = 0; i < lhs.getHeight(); i++) {
        for (uint32_t j = 0; j < lhs.getWidth(); j++) {
            matrix->setValue(i, j, lhs.getValue(i, j) + rhs.getValue(i, j));
        }
    }
    return *matrix;
}

CMatrix multMatrix(const CMatrix& lhs, const CMatrix& rhs) {
    // if the sizes of the matrices does not match
    if (rhs.getHeight() != lhs.getWidth())
        throw new MatrixException(ERROR_MULT_SIZES);
    // creates the result matrix of multiplying the given ones
    CMatrix* matrix = new CMatrix::CMatrix(lhs.getHeight(), lhs.getWidth());
    // sets the values of the new matrix
    for (uint32_t i = 0; i < lhs.getHeight(); i++) {
        for (uint32_t j = 0; j < lhs.getWidth(); j++) {
            double value = 0;
            for (uint32_t k = 0; k < rhs.getWidth(); k++)
                value += lhs.getValue(i, k) * rhs.getValue(k, j);
            matrix->setValue(i, j, value);
        }
    }
    return *matrix;
}