#include "matrix.h"
using namespace std;

//void get_distribution(){
//    vector<string> paths{/*"5","1e1","5e1","1e2", "5e2", "1e3", "5e3",*/ "1e4"/*,*/ /*"5e4"*/};
//    ofstream fout;
//    fout.open("Six_Thread_Distribution.txt", ios::app);
//    fout << "Size of square matrix" << "\t" << "Time for multiplying, s" << endl;
//    for (int i = 0; i < paths.size(); ++i){
//        matrix::matrix matrix1(stod(paths[i]), stod(paths[i]));
//        matrix::matrix matrix2(stod(paths[i]), stod(paths[i]));
//        auto start = std::chrono::high_resolution_clock::now();
//        matrix1 * matrix2;
//        auto end = std::chrono::high_resolution_clock::now();
//        fout << paths[i] << "\t" << std::chrono::duration<float>(end - start).count() << endl;
//    }
//}

template <typename T>
void Test_All_operations(){
    matrix::matrix<T> matrix2(matrix::matrix<T>::Random_matrix(4, 4));
    matrix::matrix<T> matrix1(matrix::matrix<T>::Random_matrix(4, 4));

    cout << matrix1; cout << matrix2;
    cout << "That`s multiplying result" << endl << matrix1 * matrix2;
    cout << "That`s summing result" << endl << matrix1 + matrix2;
    cout << "That`s different result" << endl << matrix1 - matrix2;
    cout << "That`s determinant result" << endl << determinant(matrix1);
    cout << "That`s inverse result" << endl << !matrix1;
//    cout << "That`s multiplying result" << endl << matrix1 * matrix2;
}

int main() {
    Test_All_operations<double>();


    return 0;
}
