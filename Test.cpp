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

    MatrixRaw nonsquare = {{1,2,3}};

    Matrix A; 
    A = test1;
    A.setName("Test1");
    cout << "cout test" << endl;
    cout << A;

    cout << "Inverted Matrix:" << endl;
    cout << Invert(A.getData());

    cout << "Transpose" << endl << "Before:" << endl;;
    cout << nonsquare << endl;
    cout << "After:" << endl;
    cout << Transpose(nonsquare) << endl;


    double det; 

    det = DeterminantSlow(A.getData());
    cout << "Determint via Laplace Expansion: " << det << endl;
    det = DeterminatFast(A.getData());
    cout << "Determinant via Gauusian Elimation: " << det << endl;

            }
        catch(string error) {
            cout << error; 
        }

    return 0;
}