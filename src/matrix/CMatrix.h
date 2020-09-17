#pragma once

#ifndef _CMATRIX_H
#define _CMATRIX_H

#include "ErrorCode.h"
#include "Matrix.h"
#include <cstdint>



class CMatrix {
    public:
        /**
         * @brief Construct a new CMatrix object.
         * 
         * @param height - height of the matrix.
         * @param width - width of the matrix.
         */
        CMatrix(uint32_t height, uint32_t width);

        /**
         * @brief Construct a new CMatrix object by copying the given one.
         * 
         * @param other - the CMatrix that we copy.
         */
        CMatrix(const CMatrix& other);

        /**
         * @brief Operates the "=" operation.
         * 
         * @param other - the CMatrix that "this" is equal to.
         * @return CMatrix& 
         */
        CMatrix& operator=(const CMatrix& other);

        /**
         * @brief Move constructor.
         * 
         * @param other - the CMatrix we copy.
         */
        CMatrix(CMatrix&& other) noexcept;

        /**
         * @brief move assignment operator.
         * 
         * @param other - the assignment that "this" is equal to.
         * @return CMatrix& 
         */
        CMatrix& operator=(CMatrix&& other) noexcept;

        /**
         * @brief Destroy the CMatrix object.
         * 
         */
        ~CMatrix();



        /**
         * @brief Get the Height of the matrix.
         * 
         * @return uint32_t 
         */
        uint32_t getHeight() const;

        /**
         * @brief Get the Width of the matrix.
         * 
         * @return uint32_t 
         */
        uint32_t getWidth() const;

        /**
         * @brief Set the Value of a cell in the matrix.
         * 
         * @param rowIndex - the row of the cell.
         * @param colIndex - the col of the cell.
         * @param value - the new value of the cell.
         */
        void setValue(uint32_t rowIndex, uint32_t colIndex, double value);

        /**
         * @brief Get the Value of a cell in the matrix.
         * 
         * @param rowIndex - the row of the cell.
         * @param colIndex - the col of the cell.
         * @return double 
         */
        double getValue(uint32_t rowIndex, uint32_t colIndex) const;

        /**
         * @brief Multiply "this" matrix with a scalar.
         * 
         * @param scalar - the scalar we multiply our matric with.
         */
        void multMatrixWithScalar(double scalar);

        /**
         * @brief Multiplying two matrices.
         * 
         * @param lhs - the left matrix.
         * @param rhs - the right matrix.
         * @return CMatrix 
         */
        static CMatrix multMatrix(const CMatrix& lhs, const CMatrix& rhs);

        /**
         * @brief Adding two matrices.
         * 
         * @param lhs - the left matrix.
         * @param rhs - the right matrix.
         * @return CMatrix 
         */
        static CMatrix add(const CMatrix& lhs,const CMatrix& rhs);
        
        /**
         * @brief Adding two matrices (like CMatrix::add).
         *        The left matrix is "this".
         * 
         * @param rhs - the right matrix.
         * @return CMatrix 
         */
        CMatrix operator+(const CMatrix& rhs) const;

        /**
         * @brief Subtracts one matrix from another.
         * 
         * @param rhs - the matrix we substruct from "this".
         * @return CMatrix 
         */
        CMatrix operator-(const CMatrix& rhs) const;

        /**
         * @brief Multiply "this" matrix with another (like CMatrix::multiplyMatrix).
         *        The left matrix is "this".
         * 
         * @param rhs - the matrix we multiply "this" with.
         * @return CMatrix 
         */
        CMatrix operator*(const CMatrix& rhs) const;

        /**
         * @brief Multiply "this" matrix with another (like CMatrix::multiplyMatrix).
         *        The left matrix is "this".
         * 
         * @param rhs - the matrix we multiply "this" with.
         * @return CMatrix 
         */
        CMatrix operator*=(const CMatrix& rhs);

        /**
         * @brief Multiply "this" matrix with scalar.
         * 
         * @param rhs - the matrix we multiply "this" with.
         * @return CMatrix 
         */
        CMatrix operator*(double scalar) const;

        /**
         * @brief Multiply "this" matrix with scalar.
         * 
         * @param rhs - the matrix we multiply "this" with.
         * @return CMatrix 
         */
        CMatrix operator*=(double scalar);

        /**
         * @brief Gets a cell value from the matrix.
         * 
         * @param rowIndex - the row of the cell.
         * @param colIndex - the col of the cell.
         * @return double 
         */
        double operator()(uint32_t rowIndex, uint32_t colIndex) const;

    private:
        PMatrix m_matrix;

        /**
         * @brief Construct a new CMatrix object from a given PMatrix object.
         *        Note that the method is private to maintain the incapsulation of the CMatrix object.
         * 
         * @param matrix - the PMatrix object we use to create the CMatrix.
         */
        explicit CMatrix(const PMatrix& matrix);
};

#endif