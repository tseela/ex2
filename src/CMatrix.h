#pragma once

#ifndef _CMATRIX_H
#define _CMATRIX_H

#include "ErrorCode.h"
#include "MatrixException.h"
#include "Matrix.h"
#include <stdint.h>

static CMatrix multMatrix(const CMatrix& lhs, const CMatrix& rhs);
static CMatrix add(const CMatrix& lhs,const CMatrix& rhs);

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
        void multMatrixWithScalar(double scalar);

    private:
        PMatrix m_matrix;

        CMatrix::CMatrix(const PMatrix& m);
};

#endif