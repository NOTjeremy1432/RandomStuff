#include "lib/Matrix.cpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
    try{
    MatrixRaw test1 = {
                {1,2,3},
                {4,5,6},
                {7,8,8}
                };
    Matrix A; 
    A = test1;
    A.setName("Test1");
    cout << "cout test" << endl;
    cout << A;
    cout << A; 

    cout << "Append and Identy test" << endl;

    Matrix B;


    B = Append(A.getData(), Identity(3));
    
    B.setName("A + Identity");

    cout << B; 

   B = GaussianJordanElimination(B.getData());

   cout << B;

            }
        catch(string error) {
            cout << error; 
        }

    return 0;
}