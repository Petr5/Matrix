#include "matrix.h"
using namespace std;

template <typename T1, typename T2>
void write_to_file(pair<T1, T2> my_pair, size_t count_thread, string name){
    ofstream fout;
     string path = to_string(count_thread) + name + "Thread_Distribution.txt";
    fout.open(path, ios::app);
    fout << my_pair.first << "\t" << my_pair.second << "\n";
    fout.close();
}

void get_distribution(size_t count_thread, string name){
    const uint64_t max_matrix = 20000;
    const uint64_t step = 1000;
    const uint64_t start = 0;
    const size_t x_size = 5;
    float time;
    int j = 0;
    for (size_t size_matrix = start; size_matrix < max_matrix; size_matrix +=step){

        matrix::matrix<int> matrix1(matrix::matrix<int>::RandomMatrix(size_matrix, size_matrix));
        matrix::matrix<int> matrix2(matrix::matrix<int>::RandomMatrix(size_matrix, size_matrix));
        time = matrix::matrix<int>::measure_time(matrix1, matrix2, name, count_thread);
        write_to_file(make_pair(size_matrix, time), count_thread, name);
        cout << j++ << endl;
    }

}

template <typename T>
void Test_All_operations(){
    matrix::matrix<T> matrix2(matrix::matrix<T>::RandomMatrix(4, 4));
    matrix::matrix<T> matrix1(matrix::matrix<T>::RandomMatrix(4, 4));

    cout << matrix1; cout << matrix2;
    cout << "That`s multiplying result" << endl << matrix1 * matrix2;
    cout << "That`s different result" << '\n' << matrix2 - matrix1;
    cout << "That`s summing result" << endl << matrix1 + matrix2;

    cout << "That`s determinant result" << endl << determinant(matrix1) << endl;
    cout << "That`s inverse result" << endl << !matrix1;
//    cout << "That`s multiplying result" << endl << matrix1 * matrix2;
}

int main() {
//    vector<int> threads{1, 2};
//    size_t count_thread = 2;
//    get_distribution(count_thread, "-");
//    count_thread = 1;
//    get_distribution(count_thread, "-");
//    for (auto el : threads)
//        get_distribution(el, "-");
//    for (auto el : threads)
//        get_distribution(el, "+");
    //    size_t size_matrix = 10000;
//    matrix::matrix<int> matrix1(matrix::matrix<int>::RandomMatrix(size_matrix, size_matrix));
//    matrix::matrix<int> matrix2(matrix::matrix<int>::RandomMatrix(size_matrix, size_matrix));
//    cout << matrix1;
//    cout << matrix2;
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "==", count_thread) << endl;
//    auto start = std::chrono::high_resolution_clock::now();
//    matrix1.equal(matrix2, count_thread);
//    auto end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<float> duration = end - start;
//    cout << duration.count();
//    cout << matrix2;
//    cout << matrix1.sum(matrix2, 4) << endl;
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "+", 1) << endl;
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "+", 2) << endl;
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "+", 4) << endl;
//    matrix::matrix<int> matrix1(matrix::matrix<int>::RandomMatrix(size_matrix, size_matrix));
//    matrix::matrix<int> matrix2(matrix::matrix<int>::RandomMatrix(size_matrix, size_matrix));
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "*", 2);
//    size_t size_matrix = 10000;
//    size_t count_thread = 3;
//    matrix::matrix<int> matrix1(matrix::matrix<int>::RandomMatrix(size_matrix, size_matrix));
//    matrix::matrix<int> matrix2(matrix::matrix<int>::RandomMatrix(size_matrix, size_matrix));

//    cout << matrix1.difference(matrix2, 3);
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "-", 1) << endl;
//    cout << matrix1.difference(matrix2, 3);
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "-", 2) << endl;
//    cout << matrix1.difference(matrix2, 3);
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "-", 3) << endl;
//    cout << matrix::matrix<int>::measure_time(matrix1, matrix2, "-", 4) << endl;

//    matrix::matrix<int> matrix1(static_cast<matrix::matrix<int>&&>(matrix::matrix<int>::RandomMatrix(4, 4)));
//    matrix::matrix<int> matrix2(matrix::matrix<int>::RandomMatrix(4, 4));
//    matrix::matrix<int> matrix5 = matrix::matrix<int>::RandomMatrix(4, 4);
//    cout << "matrix2" << matrix2;
//    matrix::matrix<int> matrix3 = move(matrix2);
////    cout << matrix1 << endl;
//    cout << "matrix3" << matrix3;
//    cout << matrix2;

//    matrix::matrix<int> matrix_initialized_by_list(
//            {
//                {1, 2, 3},
//                {3, 7, 8}
//            });
//    int arr[2][3] =
//            {
//            {1, 2, 3},
//            {3, 7, 8}
//            };
//    for (size_t i = 0; i < 2; ++i){
//        for (size_t j = 0; j < 3; ++j)
//            cout << arr[i][j] << "\t";
//        cout << endl;
//    }
//cout << matrix_initialized_by_list;
    matrix::matrix<int> matrix7(matrix::matrix<int>::RandomMatrix(4, 4));
    matrix::matrix<int> matrix8(matrix::matrix<int>::RandomMatrix(4, 4));
    cout << matrix7.difference(matrix8, 4);
    return 0;
}
