#include "lib/Matrix.cpp"
#include <iostream>
using namespace std;

int main() {
    MatrixRaw test1 = {
                {1,2,3},
                {4,5,6},
                {7,8,9}
                };
    Matrix A; 
    A = test1;
    cout << "cout test" << endl;
    cout << A;
}