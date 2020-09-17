#include "CMatrix.h"
#include "Matrix.h"
#include "ErrorCode.h"
#include <iostream>
#include <exception>
#include <memory>


CMatrix::CMatrix(uint32_t height, uint32_t width) {
    if (!error_isSuccess(matrix_create(&m_matrix, height, width))) {
       throw std::runtime_error(error_getErrorMessage(matrix_create(&m_matrix, height, width)));
    }
}

CMatrix::CMatrix(const PMatrix& matrix) {
    if (!error_isSuccess(matrix_copy(&m_matrix, matrix))) {
        throw std::runtime_error(error_getErrorMessage(matrix_copy(&m_matrix, matrix)));
    }
}

CMatrix::CMatrix(const CMatrix& other) {
    if (!error_isSuccess(matrix_copy(&m_matrix, other.m_matrix))) {
        throw std::runtime_error(error_getErrorMessage(matrix_copy(&m_matrix, other.m_matrix)));
    }
}

CMatrix& CMatrix::operator=(const CMatrix& other) {
    matrix_destroy(this->m_matrix);
    if (!error_isSuccess(matrix_copy(&m_matrix, other.m_matrix))) {
        throw std::runtime_error(error_getErrorMessage(matrix_copy(&m_matrix, other.m_matrix)));
    }
    return *this;
}

CMatrix::CMatrix(CMatrix&& other) noexcept {
    m_matrix = other.m_matrix;
    other.m_matrix = nullptr;
}

CMatrix& CMatrix::operator=(CMatrix&& other) noexcept {
    matrix_destroy(this->m_matrix);
    m_matrix = other.m_matrix;
    return *this;
}

CMatrix::~CMatrix() {
    matrix_destroy(m_matrix);
}


uint32_t CMatrix::getHeight() const {
    uint32_t height;
    if (!error_isSuccess(matrix_getHeight(m_matrix, &height))) {
        throw std::runtime_error(error_getErrorMessage(matrix_getHeight(m_matrix, &height)));
    }
    return height;
}

uint32_t CMatrix::getWidth() const {
    uint32_t width;
    if (!error_isSuccess(matrix_getWidth(m_matrix, &width))) {
        throw std::runtime_error(error_getErrorMessage(matrix_getWidth(m_matrix, &width)));
    }
    return width;
}

void CMatrix::setValue(uint32_t rowIndex, uint32_t colIndex, double value) {
    if (!error_isSuccess(matrix_setValue(m_matrix, rowIndex, colIndex, value))) {
        throw std::runtime_error(error_getErrorMessage(matrix_setValue(m_matrix, rowIndex, colIndex, value)));
    }
}

double CMatrix::getValue(uint32_t rowIndex, uint32_t colIndex) const {
    double value;
    if (!error_isSuccess(matrix_getValue(m_matrix, rowIndex, colIndex, &value))) {
        throw std::runtime_error(error_getErrorMessage(matrix_getValue(m_matrix, rowIndex, colIndex, &value)));
    }
    return value;
}

void CMatrix::multMatrixWithScalar(double scalar) {
    if (!error_isSuccess(matrix_multiplyWithScalar(m_matrix, scalar))) {
        throw std::runtime_error(error_getErrorMessage(matrix_multiplyWithScalar(m_matrix, scalar)));
    }
}


CMatrix CMatrix::add(const CMatrix& lhs, const CMatrix& rhs) {
    auto matrix = CMatrix(lhs.getHeight(), lhs.getWidth());
    if(!error_isSuccess(matrix_add(&matrix.m_matrix,lhs.m_matrix, rhs.m_matrix))) {
        throw std::runtime_error(error_getErrorMessage(matrix_add(&matrix.m_matrix,lhs.m_matrix, rhs.m_matrix)));
    }
    return matrix;
}

CMatrix CMatrix::multMatrix(const CMatrix& lhs, const CMatrix& rhs) {
    auto matrix = CMatrix(lhs.getHeight(), rhs.getWidth());
    if(!error_isSuccess(matrix_multiplyMatrices(&matrix.m_matrix,lhs.m_matrix, rhs.m_matrix))) {
        throw std::runtime_error(error_getErrorMessage(matrix_multiplyMatrices(&matrix.m_matrix,lhs.m_matrix, rhs.m_matrix)));
    }
    return matrix;
}


CMatrix CMatrix::operator+(const CMatrix& rhs) const {
    return CMatrix::add(*this, rhs);
}

CMatrix CMatrix::operator-(const CMatrix& rhs) const {
    // a - b = a + (-1.0) * b
    auto minusRhs = CMatrix(rhs);
    minusRhs.multMatrixWithScalar(-1.0);
    return add(*this, rhs);
}

CMatrix CMatrix::operator*(const CMatrix& rhs) const {
    return multMatrix(*this, rhs);
}

CMatrix CMatrix::operator*=(const CMatrix& rhs) {
    if(!error_isSuccess(matrix_multiplyMatrices(&m_matrix, this->m_matrix, rhs.m_matrix))) {
        throw std::runtime_error(error_getErrorMessage(matrix_multiplyMatrices(&m_matrix, this->m_matrix, rhs.m_matrix)));
    }
    return *this;
}

CMatrix CMatrix::operator*(double scalar) const {
    std::shared_ptr<CMatrix> result = std::make_shared<CMatrix>(*this);
    result->multMatrixWithScalar(scalar);
    return *result;
}

CMatrix CMatrix::operator*=(double scalar) {
    this->multMatrixWithScalar(scalar);
    return *this;
}

double CMatrix::operator()(uint32_t rowIndex, uint32_t colIndex) const {
    return getValue(rowIndex, colIndex);
}