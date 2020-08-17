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

        std::string getExceptionMessage() {
            return error_getErrorMessage(m_errorCode);
        }
};


class Matrix {
    PMatrix m_matrix;

    public:
        Matrix(uint32_t height, uint32_t width) {
            matrix_create(&m_matrix, height, width);
        }
        Matrix(const Matrix& m) {
            m_matrix = m.m_matrix;
        }
        
        Matrix& operator=(const Matrix& other) {
            m_matrix = other.m_matrix;
            return *this;
        }
        Matrix(Matrix&& m) noexcept {
            m_matrix = m.m_matrix;
        }

        Matrix& operator=(Matrix&& m) noexcept {




        }
        ~Matrix() {
            matrix_destroy(m_matrix);
        }

        uint32_t getHeight() {
            uint32_t height;
            matrix_getHeight(m_matrix, &height);
            return height;
        }
        uint32_t getWidth() {
            uint32_t width;
            matrix_getWidth(m_matrix, &width);
            return width;
        }
        void setValue(uint32_t rowIndex, uint32_t colIndex, double value) {
            matrix_setValue(m_matrix,rowIndex,colIndex,value);
        }
        const Matrix add(CPMatrix lhs, CPMatrix rhs) {
            PMatrix m;
            matrix_add(&m,lhs,rhs);
            return *m;
        }
        const Matrix multMatrix(CPMatrix lhs, CPMatrix rhs) {
            PMatrix m;
            matrix_multiplyMatrices(&m,lhs,rhs);
            return *m;
        }
        const void multMatrixWithScalar(PMatrix m,double scalar) {
            matrix_multiplyWithScalar(m,scalar);
        }
};