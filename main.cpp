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
    cout << "That`s different result" << '\n' << matrix2 - matrix1;
    cout << "That`s summing result" << endl << matrix1 + matrix2;

    cout << "That`s determinant result" << endl << determinant(matrix1) << endl;
    cout << "That`s inverse result" << endl << !matrix1;
//    cout << "That`s multiplying result" << endl << matrix1 * matrix2;
}

int main() {
//
////    Test_All_operations<int>();
//    matrix::matrix<int> matrix1(4,4);
//    matrix::matrix<int> matrix2{};
//    fstream fin; fin.open("4_4.txt");
//
////    fin >> matrix1;
////    fin >> matrix2;
////cin >> matrix1;
////    cout << matrix1;
//////    cout << matrix1;
////    matrix2 = matrix1;
////    cout << "That`s determinant " << determinant(matrix1) << endl;
////    cout << matrix2;
////    cout << matrix2.array[4][0];
////    matrix::matrix<double> matrixZ(matrix::matrix<double>::Random_matrix(3,3));
////    matrix::matrix<double> matrixY(matrix::matrix<double>::Random_matrix(3,3));
////    cout << matrixZ;
////    matrixZ = matrixZ;
////    cout << matrixZ;
//    matrix::matrix<int>::ReadFromFile(fin, matrix2);
//    cout << matrix2;
    int **pointer = reinterpret_cast<int **>(1);
//    **pointer = 1;
    ++*pointer;
    **pointer = 9;
    cout << **pointer << endl; --pointer; cout << pointer;
    return 0;
}
