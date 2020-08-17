#include "Matrix.h"
#include "ErrorCode.h"
class Matrix{
    public:
        Matrix(PMatrix* m, uint32_t height, uint32_t width); //regular constuctor
        Matrix(const Matrix& m); //copy constructor
        
        Matrix& operator=(const Matrix& m); //copy assignment operator
        Matrix(Matrix&& m) noexcept; //move constructor

        Matrix& operator=(Matrix&& m) noexcept; //move assignment constructor
        ~Matrix(); //destructor

        Matrix copy(PMatrix* result, CPMatrix source); //copy
        int getHeight(CPMatrix m); //accessor
        int getWidth(CPMatrix m); //accessor
        void setValue(PMatrix m, int rowIndex, int colIndex, double value); //setter
        Matrix add(CPMatrix lhs, CPMatrix rhs); 
        Matrix multMatrix(CPMatrix lhs, CPMatrix rhs); 
        Matrix multMatrixWithScalar(CPMatrix m, int scalar); 
};