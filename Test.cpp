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

    A = Append(A.getData(), Identity(3));
    A.setName("A append with Identy");
    cout << A; 

    A = GaussianJordanElimination(A.getData());
    A.setName("GaussianJordan Elimination");
    cout << A;

    A = DetachBack(3, A.getData());
    A.setName("Detach the Back");
    cout << A;

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