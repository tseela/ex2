#include "Matrix.h"
#include "ErrorCode.h"
#include <iostream>
#include <exception>

class MatrixException : public std::exception {
    ErrorCode m_errorCode;

    public:
        MatrixException(ErrorCode errorCode) {
            m_errorCode = errorCode;
        }

        std::string what() {
            return error_getErrorMessage(m_errorCode);
        }
};


class Matrix {
    PMatrix m_matrix;

    public:
        Matrix(uint32_t height, uint32_t width) throw(MatrixException) {
            if (!error_isSuccess(matrix_create(&m_matrix, height, width)))
                throw new MatrixException(matrix_create(&m_matrix, height, width));
        }
        Matrix(const Matrix& m) throw (MatrixException) {
            if (!error_isSuccess(matrix_copy(&m_matrix, m.m_matrix)))
                throw new MatrixException(matrix_copy(&m_matrix, m.m_matrix));
        }
        
        Matrix& operator=(const Matrix& other) throw(MatrixException) {
            if (!error_isSuccess(matrix_copy(&m_matrix, other.m_matrix)))
                throw new MatrixException(matrix_copy(&m_matrix, other.m_matrix));
            return *this;
        }
        Matrix(Matrix&& m) noexcept {
            m_matrix = m.m_matrix;
        }

        Matrix& operator=(Matrix&& m) noexcept {
            return *this;
        }
        ~Matrix() {
            matrix_destroy(m_matrix);
        }

        uint32_t getHeight() throw(MatrixException) {
            uint32_t height;
            if (!error_isSuccess(matrix_getHeight(m_matrix, &height)))
                throw new MatrixException(matrix_getHeight(m_matrix, &height));
            return height;
        }
        uint32_t getWidth() throw(MatrixException) {
            uint32_t width;
            if (!error_isSuccess(matrix_getWidth(m_matrix, &width)))
                throw new MatrixException(matrix_getWidth(m_matrix, &width));
            return width;
        }
        void setValue(uint32_t rowIndex, uint32_t colIndex, double value) throw(MatrixException) {
            if (!error_isSuccess(matrix_setValue(m_matrix, rowIndex, colIndex, value)))
                throw new MatrixException(matrix_setValue(m_matrix, rowIndex, colIndex, value));
        }
        const Matrix add(CPMatrix lhs, CPMatrix rhs) throw(MatrixException) {
            PMatrix m;
            ErrorCode ec = matrix_add(&m, lhs, rhs);
            if (!error_isSuccess(ec))
                throw new MatrixException(ec);
            return *m;
        }
        const Matrix multMatrix(CPMatrix lhs, CPMatrix rhs) throw(MatrixException) {
            PMatrix m;
            ErrorCode ec = matrix_multiplyMatrices(&m, lhs, rhs);
            if (!error_isSuccess(ec))
                throw new MatrixException(ec);
            return *m;
        }
        void multMatrixWithScalar(double scalar) throw(MatrixException) {
            if (!error_isSuccess(matrix_multiplyWithScalar(m_matrix, scalar)))
                throw new MatrixException(matrix_multiplyWithScalar(m_matrix, scalar));
        }
};