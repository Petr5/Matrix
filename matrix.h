
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
#include <ctime>
#include <mutex>
#include <windows.h>

using std::cout; using std::endl;
namespace matrix{

    template <typename T>
    struct matrix {
    private:
        struct ThreadArgs{
            size_t type;
            matrix<T>* res;
            T multiplier;
            const matrix<T>* pYourClass;
           ThreadArgs(){
               type = 0;
               res = nullptr;
               multiplier = 0;
               pYourClass = nullptr;
           }
           ThreadArgs(matrix<T>* res, size_t type, T multiplier, const matrix<T>* pYourClass){
               this->type = type;
               this->res = res;
               this->multiplier = multiplier;
               this->pYourClass = pYourClass;
           }
           ThreadArgs(const ThreadArgs& other){
               type = other.type;
               res = other.res;
               multiplier = other.multiplier;
               pYourClass = other.pYourClass;
           }
        };
        T** array = nullptr;
        size_t x_size = 0;
        size_t y_size = 0;
    public:
        static matrix identity_matrix(size_t size){
            matrix matrix(size);
            size_t j = 0;
            while (j < size){
                matrix.array[j] = new T[size];
                for (int i = 0; i < size; ++i){if (i == j) matrix.array[j][i] = 1; else matrix.array[j][i] = 0;}
                ++j;
            }
            return matrix;
        }
        static matrix zero_matrix(size_t size){
            matrix matrix(size);
            size_t j = 0;
            while (j < size){
                matrix.array[j] = new T[size];
                for (int i = 0; i < size; ++i){matrix.array[j][i] = 0;}
                ++j;
            }
            return matrix;
        }
        matrix(){
            array = nullptr;
            x_size = 0;
            y_size = 0;
        }
        explicit matrix(const std::string& path) {
            std::ifstream fin;
            fin.open(path);
            if(!fin) { // file couldn't be opened
                std::cerr << "Error: file " << path << " could not be opened" << std::endl;
                exit(1);
            }
            fin >> *this;
        }

        explicit matrix(size_t Size){
            this->y_size = this->x_size = Size;
            this->array = new T* [Size];
            for (int j = 0; j < Size; ++j) {
                this->array[j] = new T[Size];
            }
        }

        matrix(size_t y_size, size_t x_size){
            this->y_size= y_size; this->x_size = x_size;
            this->array = new T* [y_size];
            for (int j = 0; j < y_size; ++j) {
                this->array[j] = new T[x_size];
            }
        }
        matrix(const matrix& other){
            this->~matrix();
            this->y_size = other.y_size; this->x_size = other.x_size;

            this->array = new T* [this->y_size];
            for (size_t i = 0; i < this->y_size; ++i){
                this->array[i] = new T [this->x_size];
                for (size_t j = 0; j < this->x_size; ++j)
                    this->array[i][j] = other.array[i][j];
            }
        }
        matrix<T>& operator =(const matrix& other){
            this->y_size = other.y_size; this->x_size = other.x_size;
            T** pointer;
            pointer = new T* [this->y_size];
            for (size_t i = 0; i < this->y_size; ++i){
                pointer[i] = new T [this->x_size];
                for (size_t j = 0; j < this->x_size; ++j)
                    pointer[i][j] = other.array[i][j];
            }
            this->~matrix();
            this->array = pointer;
            return *this;
        }
        ~matrix(){
            if (this->array){
                for (size_t i = 0; i < this->y_size; ++i)
                    delete [] this->array[i];
                delete [] this->array;
            }
            this->array = nullptr;
        }
        friend double determinant(const matrix<T>& matrix1) {
            if (matrix1.x_size != matrix1.y_size) {
                throw std::invalid_argument("For calculate determinant matrix should be square");
            }
            else
            {
                size_t n = matrix1.x_size;
                matrix temp(matrix1);
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
        void half_row_sum_half_column(const matrix &other, const matrix &res, size_t type) const {
            std::cout << "STARTED " << std::this_thread::get_id() << std::endl;
            if (!type) {
                for (size_t row = 0; row < this->y_size / 2; ++row)
                    for (size_t column = 0; column < other.x_size / 2; ++column) {
                        res.array[row][column] = this->array[row][column] + other.array[row][column];
                    }
            }
            if (type == 1) {
                for (size_t row = 0; row < this->y_size / 2; ++row)
                    for (size_t column = other.x_size / 2; column < other.x_size; ++column) {
                        res.array[row][column] = this->array[row][column] + other.array[row][column];
                    }
            }
            if (type == 2) {
                for (size_t row = this->y_size / 2; row < this->y_size; ++row)
                    for (size_t column = 0; column < other.x_size / 2; ++column) {
                        res.array[row][column] = this->array[row][column] + other.array[row][column];
                    }
            }
            std::cout << "ENDED " << std::this_thread::get_id() << std::endl;
        }
        void half_row_difference_half_column(const matrix<T> &other, const matrix<T> &res, size_t type) const{
            std::cout << "STARTED " << std::this_thread::get_id() << std::endl;
            if (!type) {
                for (size_t row = 0; row < this->y_size / 2; ++row)
                    for (size_t column = 0; column < other.x_size / 2; ++column) {
                        res.array[row][column] = this->array[row][column] - other.array[row][column];
                    }
            }
            if (type == 1) {

                for (size_t row = 0; row < this->y_size / 2; ++row)
                    for (size_t column = other.x_size / 2; column < other.x_size; ++column) {
                        res.array[row][column] = this->array[row][column] - other.array[row][column];
                    }
            }
            if (type == 2) {
                for (size_t row = this->y_size / 2; row < this->y_size; ++row)
                    for (size_t column = 0; column < other.x_size / 2; ++column) {
                        res.array[row][column] = this->array[row][column] - other.array[row][column];
                    }
            }

            std::cout << "ENDED " << std::this_thread::get_id() << std::endl;
        }
        void half_row_multiply_half_column(const matrix<T>& other,const matrix<T>& res, size_t type) const{
            std::cout << "STARTED " << std::this_thread::get_id() << std::endl;
            if (!type) {
                for (size_t row = 0; row < this->y_size / 2; ++row)
                    for (size_t column = 0; column < other.x_size / 2; ++column) {
                        double sum = 0;
                        for (size_t g = 0; g < this->x_size; ++g)
                            sum += this->array[row][g] * other.array[g][column];
                        res.array[row][column] = sum;
                    }
            }
            if (type == 1) {

                for (size_t row = 0; row < this->y_size / 2; ++row)
                    for (size_t column = other.x_size / 2; column < other.x_size; ++column) {
                        double sum = 0;
                        for (size_t g = 0; g < this->x_size; ++g)
                            sum += this->array[row][g] * other.array[g][column];
                        res.array[row][column] = sum;
                    }
            }
            if (type == 2) {
                for (size_t row = this->y_size / 2; row < this->y_size; ++row)
                    for (size_t column = 0; column < other.x_size / 2; ++column) {
                        double sum = 0;
                        for (size_t g = 0; g < this->x_size; ++g)
                            sum += this->array[row][g] * other.array[g][column];
                        res.array[row][column] = sum;
                    }
            }

            std::cout << "ENDED " << std::this_thread::get_id() << std::endl;
        }
        matrix<T> operator* (const matrix<T>& other) const{
            auto start = std::chrono::high_resolution_clock::now();
            if (this->x_size != other.y_size){
                std::cerr << "Number of columns first matrix must be equal to number of rows second matrix";
                exit(1);
            }
            {
                matrix res(this->y_size, other.x_size);
                std::vector<std::thread> threads;
                for (size_t i = 0; i < 3; ++i)
                {
                    threads.emplace_back([&other, &res, i, this](){half_row_multiply_half_column(other, res, i); });
                }
                for (size_t row = this->y_size / 2; row < this->y_size; ++row)
                    for (size_t column =  other.x_size / 2; column < other.x_size ; ++column){
                        double sum = 0;
                        for (size_t g = 0; g < this->x_size; ++g)
                            sum += this->array[row][g] * other.array[g][column];
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


        friend matrix<T> Gaus(const matrix<T>& other){
            size_t n = other.x_size;
            matrix temp(other);
            matrix identity = identity_matrix(other.y_size);

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
                    K = static_cast<double>(temp.array[i][row]) / temp.array[row][row];
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
                    K = static_cast<double>(temp.array[i][row]) / temp.array[row][row];
                    temp.array[i][row] = temp.array[i][row] - temp.array[row][row] * K;
                    for (int j = 0; j < n; ++j)
                        identity.array[i][j] = identity.array[i][j] - identity.array[row][j] * K;
                }
            }
            return identity;
        }

        static DWORD WINAPI MyFIRSTThreadFunction(ThreadArgs* args){
            std::cout << "THREAD " << GetCurrentThreadId() << " STARTED" << std::endl;
            auto begin = std::chrono::high_resolution_clock::now();

            args->pYourClass->ThreadFunc(args);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - begin;
            std::cout << "THREAD " << GetCurrentThreadId() << " ENDED " << duration.count() << std::endl;
            return 0;
        }
        void ThreadFunc(ThreadArgs* args) const{
            if (!args->type){
                Sleep(20000);
                for (size_t i = 0; i < this->y_size / 2; ++i)
                    for (size_t j = 0; j < this->x_size / 2; ++j)
                        args->res->array[i][j] = this->array[i][j] * args->multiplier;
            }

            if (args->type == 1){
                Sleep(10000);
                for (size_t i = 0; i < this->y_size / 2; ++i)
                    for (size_t j = this->x_size / 2; j < this->x_size; ++j)
                        args->res->array[i][j] = this->array[i][j] * args->multiplier;
            }

            if (args->type == 2){
                for (size_t i = this->y_size / 2; i < this->y_size; ++i)
                    for (size_t j = 0; j < this->x_size / 2; ++j)
                        args->res->array[i][j] = this->array[i][j] * args->multiplier;
            }
        }

        matrix<T> operator* (const double multiplier) const{
            matrix res(this->y_size, this->x_size);
            HANDLE Threads_Handles_Array[3];
            std::vector<ThreadArgs> argsArray(3);
            for (size_t i = 0; i < 3; ++i){
                argsArray[i] = ThreadArgs(&res, i, multiplier, this);
                Threads_Handles_Array[i] =
                        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) &MyFIRSTThreadFunction, &argsArray[i], 0, nullptr);
            }
            WaitForMultipleObjects(3, Threads_Handles_Array,TRUE, INFINITE);
            for (size_t i = 0; i < 3; ++i){
                CloseHandle(Threads_Handles_Array[i]);
            }
            for (size_t i = this->y_size / 2; i < this->y_size; ++i)
                for (size_t j = this->x_size / 2; j < this->x_size; ++j)
                    res.array[i][j] = this->array[i][j] * multiplier;
            return res;
        }

        matrix<T> operator+ (const matrix& other) const{
            auto start = std::chrono::high_resolution_clock::now();
            if (this->x_size != other.x_size || this->y_size != other.y_size){
                std::cerr << "Error: Impossible sum up matrices which have different shape";
                exit(1);
            }
            else{
                matrix res(this->y_size, other.x_size);
                std::vector<std::future<void>> futures;
                futures.reserve(3);
                for (size_t i = 0; i < 3; ++i)
                {
                    futures.emplace_back(std::async(std::launch::async, [this, &other, &res, i](){ half_row_sum_half_column(other, res, i);}));
                }

                for (size_t i = other.y_size / 2; i < other.y_size; ++i){
                    for (size_t j = other.x_size / 2; j < other.x_size; ++j)
                        res.array[i][j] = this->array[i][j] + other.array[i][j];
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

        matrix<T> operator- (const matrix& other) const{
            auto start = std::chrono::high_resolution_clock::now();
            if (this->x_size != other.x_size || this->y_size != other.y_size){
                std::cerr << "Error: Impossible sum up matrices which have different shape";
                exit(1);
            }
            else{
                matrix res(this->y_size, other.x_size);
                std::vector<std::future<void>> futures;
                futures.reserve(3);
                for (size_t i = 0; i < 3; ++i)
                {
                    futures.emplace_back(std::async(std::launch::async, [this, &other, &res, i](){ half_row_difference_half_column(other, res, i);}));
                }

                for (size_t i = other.y_size / 2; i < other.y_size; ++i){
                    for (size_t j = other.x_size / 2; j < other.x_size; ++j)
                        res.array[i][j] = other.array[i][j] - this->array[i][j];
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
        bool operator ==(const matrix& other) const{
            if (this->x_size != other.x_size || this->y_size != other.y_size) return false;
            for (size_t i = 0; i < other.y_size; ++i)
                for (size_t j = 0; j < other.x_size; ++j)
                    if (array[i][j] != other.array[i][j])
                        return false;
            return true;
        }
        bool operator !=(const matrix& other) const{
            return !(*this == other);
        }
        bool operator ==(const short number){
            if (x_size != y_size) throw std::invalid_argument("Impossible to compare not square matrix with number");
            if (!number) return *this == zero_matrix(x_size);
            if (number == 1) return *this == identity_matrix(x_size);
            throw std::invalid_argument("Impossible to compare matrix with number other than 0 and 1");
        }
        friend matrix<T> operator!(const matrix<T> &other) {
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
        static void ReadFromFile(std::istream &is,  matrix<T> &matrix){
            std::string str;
            size_t i = 0;
            while (std::getline(is, str)){
                std::string delimiter = " ";
                size_t pos_start = 0, pos_end, delim_len = delimiter.length();
                std::string token;
                size_t j = 0;
                while ((pos_end = str.find (delimiter, pos_start)) != std::string::npos) {
                    token = str.substr (pos_start, pos_end - pos_start);
                    pos_start = pos_end + delim_len;
//                    matrix.array[i][j] = stoi(token);
                    *(*(matrix.array + i) + j) = stoi(token);
                    ++j;
                }
//                matrix.array[i][j] = stoi(str.substr (pos_start));
                *(*(matrix.array + i) + j) = stoi(str.substr (pos_start));
                ++i;
            }
        }
        static matrix<T> Random_matrix(size_t y_size, size_t x_size){
//            srand (time(nullptr));
            matrix random_matrix(y_size, x_size);
            for (size_t i = 0; i < y_size; ++i){
                for (size_t j = 0; j < x_size; ++j){
                    random_matrix.array[i][j] = rand();
                }

            }
            return random_matrix;
        }
        friend std::istream &operator >>(std::istream &is,  matrix<T> &matrix) {
            size_t y_size, x_size;
//            std::cout << "Please type height and then length of matrix" << std::endl;
            is >> y_size >> x_size;
//            std::cout << "Then type values" << std::endl;
            if (matrix.y_size != y_size || matrix.x_size != x_size) {
//            std::cerr << "Error: Shape of given matrix and matrix from file don`t corresponding";
//            exit(1);
                for (size_t i = 0; i < matrix.y_size; ++i)
                    delete[] matrix.array[i];
                delete[] matrix.array;
                matrix.array = new T *[y_size];
                for (size_t i = 0; i < y_size; ++i) {
                    matrix.array[i] = new T[x_size];
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
        friend std::ostream &operator<<(std::ostream &os, const struct matrix<T> &matrix) {
            for (int i = 0; i < matrix.y_size; ++i) {
                for (int j = 0; j < matrix.x_size; ++j)
                    os << matrix.array[i][j] << "\t";
                os << std::endl;
            }
            os << std::endl;
            return os;
        }
        friend std::ofstream& operator << (std::ofstream& of, const matrix<T> & matrix){
            of << matrix.y_size << "\t" << matrix.x_size << "\n";
            for (int i = 0; i < matrix.y_size; ++i) {
                for (int j = 0; j < matrix.x_size; ++j)
                    of << matrix.array[i][j] << "\t";
                of << "\n";
            }
            return of;
        }
        /*friend std::ifstream& operator >>(std::ifstream& fin, matrix<T> & matrix){
            size_t y_size, x_size;
            fin >> y_size >> x_size;
            matrix.y_size = y_size; matrix.x_size = x_size;
            matrix.array = new T* [y_size];
            for (size_t i = 0; i < y_size; ++i){
                matrix.array[i] = new T [x_size];
                for (size_t j = 0; j < x_size; ++j){
                    fin >> matrix.array[i][j];
                }
            }
            return fin;
        }*/

//        matrix operator/ (const double& a) const;

    };
}



#endif //LAB_2MOD_MATRIX_H
