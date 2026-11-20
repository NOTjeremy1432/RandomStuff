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
    A.setName("Test1");
    cout << "cout test" << endl;
    cout << A;

    A = A * A;
    cout << A; 
    return 0;
}