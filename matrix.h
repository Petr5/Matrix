
#ifndef LAB_2MOD_MATRIX_H
#define LAB_2MOD_MATRIX_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <thread>
#include <future>
#include <mutex>

namespace matrix{
    template <typename T>
    struct matrix {
    public:
        unsigned int x_size = 0;
        unsigned int y_size = 0;
        T **array = nullptr;
        explicit matrix(const std::string& path = "matrix.txt");
        ~matrix();
        static matrix identity_matrix(size_t size){
           matrix matrix(size);
           size_t j = 0;
           while (j < size){
               matrix.array[j] = new double[size];
               for (int i = 0; i < size; ++i){if (i == j) matrix.array[j][i] = 1; else matrix.array[j][i] = 0;}
               ++j;
           }
           return matrix;
       }
        static matrix zero_matrix(size_t size){
           matrix matrix(size);
           size_t j = 0;
           while (j < size){
               matrix.array[j] = new double[size];
               for (int i = 0; i < size; ++i){matrix.array[j][i] = 0;}
               ++j;
           }
           return matrix;
       }
        explicit matrix(size_t Size);
        matrix(size_t x_size, size_t y_size);
        matrix(const matrix& other);
        friend std::ifstream& operator >> (std::ifstream& fin, matrix<T>& matrix);
        friend std::istream &operator >>(std::istream &is,  matrix &matrix);
        friend std::ostream &operator<<(std::ostream &os, const matrix &matrix);
        friend std::ofstream& operator << (std::ofstream& of, const matrix & matrix);
        matrix<T>& operator+ (const matrix<T>& other) const;
        matrix<T>& operator- (const matrix& other) const;
        matrix<T>& operator* (const matrix& other) const;
        matrix<T> operator* (const double& a) const;
        friend matrix operator!(const matrix& other);
        friend double determinant(const matrix& matrix);
        void half_row_multiply_half_column(const matrix& other,const matrix& res, size_t type) const;
        void half_row_sum_half_column(const matrix &other, const matrix &res, size_t type) const;
        void half_row_difference_half_column(const matrix &other, const matrix &res, size_t type) const;
        friend matrix Gaus(const matrix& other);
        static matrix<T>& Random_matrix(size_t y_size, size_t x_size);

//        matrix operator/ (const double& a) const;

    };
}



#endif //LAB_2MOD_MATRIX_H
