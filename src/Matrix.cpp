#include "Matrix.h"
#include "ErrorCode.h"
class Matrix {
    PMatrix m_matrix;

    public:
        Matrix(PMatrix* m, uint32_t height, uint32_t width) {




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



        }

        Matrix copy(PMatrix* result, CPMatrix source) {







        }
        int getHeight(CPMatrix m) {






        }
        int getWidth(CPMatrix m) {







        }
        void setValue(PMatrix m, int rowIndex, int colIndex, double value) {







        }
        Matrix add(CPMatrix lhs, CPMatrix rhs) {






        }
        Matrix multMatrix(CPMatrix lhs, CPMatrix rhs) {






        }
        Matrix multMatrixWithScalar(CPMatrix m, int scalar) {







        }
};