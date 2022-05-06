
#include "matrix.h"

namespace matrix{


    matrix::matrix(const std::string& path) {
        std::ifstream fin;
        fin.open(path);
        if(!fin) { // file couldn't be opened
            std::cerr << "Error: file " << path << " could not be opened" << std::endl;
            exit(1);
        }
        fin >> *this;
    }

    matrix::matrix(size_t Size){
        y_size = x_size = Size;
        array = new double* [Size];
        for (int j = 0; j < Size; ++j) {
            array[j] = new double[Size];
        }
    }
    matrix::matrix(size_t y_size, size_t x_size){
        this->y_size= y_size; this->x_size = x_size;
        array = new double* [y_size];
        for (int j = 0; j < y_size; ++j) {
            array[j] = new double[x_size];
        }
    }
    matrix::matrix(const matrix& other){
        y_size = other.y_size; x_size = other.x_size;
        this->~matrix();
        array = new double* [y_size];
        for (size_t i = 0; i < y_size; ++i){
            array[i] = new double [x_size];
            for (size_t j = 0; j < x_size; ++j)
                array[i][j] = other.array[i][j];
        }
    }
//    matrix::~matrix(){
//        if (array){
//            for (size_t i = 0; i < y_size; ++i)
//                if (array[i]) delete [] array[i];
//            delete [] array;
//        }
//
//    }

    double determinant(const matrix& matrix) {
        if (matrix.x_size != matrix.y_size) {
            throw std::invalid_argument("For calculate determinant matrix should be square");
        }
        else
        {
            size_t n = matrix.x_size;
            struct matrix temp(matrix);
            double product_of_multiplying = 1;
            for (size_t row = 0; row < n; ++row)
            {
                if (!temp.array[row][row]){

                    size_t find_non_zero = row;
                    while (find_non_zero < n && temp.array[find_non_zero][row] == 0) {++find_non_zero;}
                    if (find_non_zero >= n) return 0;
                    std::swap(temp.array[find_non_zero], temp.array[row]);
                }
                double first_val_in_row = temp.array[row][row];
                for (size_t column = 0; column < n; ++column){
                    temp.array[row][column] = temp.array[row][column] / first_val_in_row;
                }
                product_of_multiplying *= first_val_in_row;
                for (size_t i = row + 1; i < n; i++)
                {
                    double K;
                    if (temp.array[i][row] == 0) continue;
                    K = temp.array[i][row] / temp.array[row][row];
                    for (int j = 0; j < n; ++j){
                        temp.array[i][j] = temp.array[i][j] - temp.array[row][j] * K;
                    }
                }
            }
            for (size_t i = 0; i < n; ++i) product_of_multiplying *= temp.array[i][i];
            return product_of_multiplying;
        }
    }
    void matrix::half_row_sum_half_column(const matrix &other, const matrix &res, size_t type) const {
        std::cout << "STARTED " << std::this_thread::get_id() << std::endl;
        if (!type) {
            for (size_t row = 0; row < y_size / 2; ++row)
                for (size_t column = 0; column < other.x_size / 2; ++column) {
                    res.array[row][column] = array[row][column] + other.array[row][column];
                }
        }
        if (type == 1) {
            for (size_t row = 0; row < y_size / 2; ++row)
                for (size_t column = other.x_size / 2; column < other.x_size; ++column) {
                    res.array[row][column] = array[row][column] + other.array[row][column];
                }
        }
        if (type == 2) {
            for (size_t row = y_size / 2; row < y_size; ++row)
                for (size_t column = 0; column < other.x_size / 2; ++column) {
                    res.array[row][column] = array[row][column] + other.array[row][column];
                }
        }
        std::cout << "ENDED " << std::this_thread::get_id() << std::endl;
    }
    void matrix::half_row_difference_half_column(const matrix &other, const matrix &res, size_t type) const{
        std::cout << "STARTED " << std::this_thread::get_id() << std::endl;
        if (!type) {
            for (size_t row = 0; row < y_size / 2; ++row)
                for (size_t column = 0; column < other.x_size / 2; ++column) {
                    res.array[row][column] = array[row][column] - other.array[row][column];
                }
        }
        if (type == 1) {

            for (size_t row = 0; row < y_size / 2; ++row)
                for (size_t column = other.x_size / 2; column < other.x_size; ++column) {
                    res.array[row][column] = array[row][column] - other.array[row][column];
                }
        }
        if (type == 2) {
            for (size_t row = y_size / 2; row < y_size; ++row)
                for (size_t column = 0; column < other.x_size / 2; ++column) {
                    res.array[row][column] = array[row][column] - other.array[row][column];
                }
        }

        std::cout << "ENDED " << std::this_thread::get_id() << std::endl;
    }
    void matrix::half_row_multiply_half_column(const matrix& other,const matrix& res, size_t type) const{
        std::cout << "STARTED " << std::this_thread::get_id() << std::endl;
        if (!type) {
            for (size_t row = 0; row < y_size / 2; ++row)
                for (size_t column = 0; column < other.x_size / 2; ++column) {
                    double sum = 0;
                    for (size_t g = 0; g < x_size; ++g)
                        sum += array[row][g] * other.array[g][column];
                    res.array[row][column] = sum;
                }
        }
        if (type == 1) {

            for (size_t row = 0; row < y_size / 2; ++row)
                for (size_t column = other.x_size / 2; column < other.x_size; ++column) {
                    double sum = 0;
                    for (size_t g = 0; g < x_size; ++g)
                        sum += array[row][g] * other.array[g][column];
                    res.array[row][column] = sum;
                }
        }
        if (type == 2) {
            for (size_t row = y_size / 2; row < y_size; ++row)
                for (size_t column = 0; column < other.x_size / 2; ++column) {
                    double sum = 0;
                    for (size_t g = 0; g < x_size; ++g)
                        sum += array[row][g] * other.array[g][column];
                    res.array[row][column] = sum;
                }
        }

        std::cout << "ENDED " << std::this_thread::get_id() << std::endl;
    }

    matrix matrix::operator* (const matrix& other) const{
        auto start = std::chrono::high_resolution_clock::now();
        if (x_size != other.y_size){
            std::cerr << "Number of columns first matrix must be equal to number of rows second matrix";
            exit(1);
        }
        {
            matrix res(y_size, other.x_size);
            std::vector<std::thread> threads;
            for (size_t i = 0; i < 3; ++i)
            {
                threads.emplace_back([&other, &res, i, this](){half_row_multiply_half_column(other, res, i); });
            }
            for (size_t row = y_size / 2; row < y_size; ++row)
                for (size_t column =  other.x_size / 2; column < other.x_size ; ++column){
                    double sum = 0;
                    for (size_t g = 0; g < x_size; ++g)
                        sum += array[row][g] * other.array[g][column];
                    res.array[row][column] = sum;
                }
            for (int i = 0; i < threads.size(); ++i)
                if (threads[i].joinable())
                    threads[i].join();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;
            std::cout << "Multiply matrix with Four THREAD have taken " << duration.count() << " second" << std::endl;
            return res;
        }
    }


    matrix Gaus(const matrix& other){
        size_t n = other.x_size;
        matrix temp(other);
        matrix identity = matrix::identity_matrix(other.y_size);

        for (size_t row = 0; row < n; ++row)
        {
            if (!temp.array[row][row]){
                size_t find_non_zero = row;
                while (temp.array[find_non_zero][row] == 0) ++find_non_zero;
                std::swap(temp.array[find_non_zero], temp.array[row]);
                std::swap(identity.array[find_non_zero], identity.array[row]);
            }
            double first_val_in_row = temp.array[row][row];
            for (size_t column = 0; column < n; ++column){
                temp.array[row][column] = temp.array[row][column] / first_val_in_row;
                identity.array[row][column] = identity.array[row][column] / first_val_in_row;
            }
            for (size_t i = row + 1; i < n; i++)
            {
                double K;
                if (temp.array[i][row] == 0) continue;
                K = temp.array[i][row] / temp.array[row][row];
                for (int j = 0; j < n; ++j){
                    temp.array[i][j] = temp.array[i][j] - temp.array[row][j] * K;
                    identity.array[i][j] = identity.array[i][j] - identity.array[row][j] * K;
                }
            }
        }
        for (int64_t row = n - 1; row >= 0; --row) {
            for (int64_t i = row - 1; i >= 0; --i) {
                double K;
                if (temp.array[i][row] == 0) continue;
                K = temp.array[i][row] / temp.array[row][row];
                temp.array[i][row] = temp.array[i][row] - temp.array[row][row] * K;
                for (int j = 0; j < n; ++j)
                    identity.array[i][j] = identity.array[i][j] - identity.array[row][j] * K;
            }
        }
        return identity;
    }
    matrix matrix::operator* (const double& a) const{
        matrix ans(y_size, x_size);
        for (size_t i = 0; i < y_size; ++i)
            for (size_t j = 0; j < x_size; ++j)
                ans.array[i][j] = array[i][j] * a;
        return ans;
    }
    matrix matrix::operator+ (const matrix& other) const{
        auto start = std::chrono::high_resolution_clock::now();
        if (x_size != other.x_size || y_size != other.y_size){
            std::cerr << "Error: Impossible sum up matrices which have different shape";
            exit(1);
        }
        else{
            matrix res(y_size, other.x_size);
            std::vector<std::future<void>> futures;
            futures.reserve(3);
            for (size_t i = 0; i < 3; ++i)
            {
                futures.emplace_back(std::async(std::launch::async, [this, &other, &res, i](){ half_row_sum_half_column(other, res, i);}));
            }

            for (size_t i = other.y_size / 2; i < other.y_size; ++i){
                for (size_t j = other.x_size / 2; j < other.x_size; ++j)
                    res.array[i][j] = array[i][j] + other.array[i][j];
            }
            for (size_t i = 0; i < 3; ++i){
                futures[i].wait();
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;
            std::cout << "Sum up matrices with Four THREAD have taken " << duration.count() << " second" << std::endl;
            return res;
        }

    }
    matrix matrix::operator- (const matrix& other) const{
        auto start = std::chrono::high_resolution_clock::now();
        if (x_size != other.x_size || y_size != other.y_size){
            std::cerr << "Error: Impossible sum up matrices which have different shape";
            exit(1);
        }
        else{
            matrix res(y_size, other.x_size);
            std::vector<std::future<void>> futures;
            futures.reserve(3);
            for (size_t i = 0; i < 3; ++i)
            {
                futures.emplace_back(std::async(std::launch::async, [this, &other, &res, i](){ half_row_difference_half_column(other, res, i);}));
            }

            for (size_t i = other.y_size / 2; i < other.y_size; ++i){
                for (size_t j = other.x_size / 2; j < other.x_size; ++j)
                    res.array[i][j] = array[i][j] - other.array[i][j];
            }
            for (size_t i = 0; i < 3; ++i){
                futures[i].wait();
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;
            std::cout << "To calc difference matrices with Four THREAD have taken " << duration.count() << " second" << std::endl;
            return res;
        }
    }

    matrix operator!(const matrix &other) {
        try {
            double det = determinant(other);
            if (det == 0){
                throw std::invalid_argument("Error: Impossible to reverse matrix which have non zero determinant");
            }
            return Gaus(other);
        }
        catch(const std::exception& ex){
            std::cerr << ex.what();
        }

    }
    std::istream &operator >>(std::istream &is,  matrix &matrix) {
        size_t y_size, x_size;
        std::cout << "Please type height and then length of matrix" << std::endl;
        is >> y_size >> x_size;
        std::cout << "Then type values" << std::endl;
        if (matrix.y_size != y_size || matrix.x_size != x_size) {
//            std::cerr << "Error: Shape of given matrix and matrix from file don`t corresponding";
//            exit(1);
            for (size_t i = 0; i < matrix.y_size; ++i)
                delete[] matrix.array[i];
            delete[] matrix.array;
            matrix.array = new double *[y_size];
            for (size_t i = 0; i < y_size; ++i) {
                matrix.array[i] = new double[x_size];
            }
            matrix.y_size = y_size;
            matrix.x_size = x_size;
        }
        for (int i = 0; i < matrix.y_size; ++i) {
            for (int j = 0; j < matrix.x_size; ++j){
                is >> matrix.array[i][j];
            }
        }
        return is;
    }
    std::ostream &operator<<(std::ostream &os, const struct matrix &matrix) {
        for (int i = 0; i < matrix.y_size; ++i) {
            for (int j = 0; j < matrix.x_size; ++j)
                os << matrix.array[i][j] << "\t";
            os << std::endl;
        }
        os << std::endl;
        return os;
    }
    std::ofstream& operator << (std::ofstream& of, const matrix & matrix){
        of << matrix.y_size << "\t" << matrix.x_size << "\n";
        for (int i = 0; i < matrix.y_size; ++i) {
            for (int j = 0; j < matrix.x_size; ++j)
                of << matrix.array[i][j] << "\t";
            of << "\n";
        }
        return of;
    }
    std::ifstream& operator >>(std::ifstream& fin, matrix & matrix){
        size_t y_size, x_size;
        fin >> y_size >> x_size;
        matrix.y_size = y_size; matrix.x_size = x_size;
        matrix.array = new double* [y_size];
        for (size_t i = 0; i < y_size; ++i){
            matrix.array[i] = new double [x_size];
            for (size_t j = 0; j < x_size; ++j){
                fin >> matrix.array[i][j];
            }
        }
        return fin;
    }

     matrix matrix::Random_matrix(size_t y_size, size_t x_size){
        srand (time(NULL));
        matrix random_matrix(y_size, x_size);
        for (size_t i = 0; i < y_size; ++i){
            for (size_t j = 0; j < x_size; ++j){
                random_matrix.array[i][j] = rand();
            }

        }
        return random_matrix;
    }

}