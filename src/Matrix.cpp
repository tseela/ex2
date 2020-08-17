#include "Matrix.h"
#include "ErrorCode.h"
class Matrix {
    PMatrix m_matrix;

    public:
        Matrix(uint32_t height, uint32_t width) {
            matrix_create(&m_matrix, height, width);



        }
        Matrix(const Matrix& m) {
            



        }
        
        Matrix& operator=(const Matrix& m) {




        }
        Matrix(Matrix&& m) noexcept {




        }

        Matrix& operator=(Matrix&& m) noexcept {




        }
        ~Matrix() {
            matrix_destroy(m_matrix);
            

        }

        Matrix copy(CPMatrix copy) {







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
        Matrix add(CPMatrix lhs, CPMatrix rhs) {
            PMatrix m;
            matrix_add(&m,lhs,rhs);
            return *m;



        }
        Matrix multMatrix(CPMatrix lhs, CPMatrix rhs) {
            PMatrix m;
            matrix_multiplyMatrices(&m,lhs,rhs);
            return *m;



        }
        void multMatrixWithScalar(double scalar) {
            matrix_multiplyWithScalar(m_matrix,scalar);
            





        }
};