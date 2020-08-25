#pragma once

#ifndef _CMATRIX_H
#define _CMATRIX_H

#include "ErrorCode.h"
#include "Matrix.h"
#include <stdint.h>



class CMatrix {
    public:
        CMatrix(uint32_t height, uint32_t width);
        CMatrix(const CMatrix& m);
        CMatrix& operator=(const CMatrix& other);
        CMatrix(CMatrix&& m) noexcept;
        CMatrix& operator=(CMatrix&& m) noexcept;
        ~CMatrix();

        uint32_t getHeight() const;
        uint32_t getWidth() const;
        void setValue(uint32_t rowIndex, uint32_t colIndex, double value);
        double getValue(uint32_t rowIndex, uint32_t colIndex) const;
        void multMatrixWithScalar(double scalar);

        static CMatrix multMatrix(const CMatrix& lhs, const CMatrix& rhs);
        static CMatrix add(const CMatrix& lhs,const CMatrix& rhs);
        
        CMatrix operator+(const CMatrix& rhs) const;
        CMatrix operator-(const CMatrix& rhs) const;
        CMatrix operator*(const CMatrix& rhs) const;
        double operator()(uint32_t rowIndex, uint32_t colIndex) const;

    private:
        PMatrix m_matrix;

        CMatrix(const PMatrix& m);
};

#endif