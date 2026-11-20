#ifndef Matrix_cpp
#define Matrix_cpp

using namespace std;

#include <vector>
#include <string>
#include <ostream>

using MatrixRaw = vector<vector<double>>;


class Matrix
{
private:
    MatrixRaw data; 
    // data[Row][Columns]
    string name;

public:

    Matrix(/* args */);
    ~Matrix();

    void setName(string Name){
        name = Name;
    }

    string getName() const {
        return name;
    }

    int getRows() const {
        if(data.empty()) throw "GetRows Error data is empty";
        return data.size();
    }
    
    int getColumns() const {
        if(data.empty()) throw "GetRows Error data is empty";
        return data[0].size();
    }

    void setData(const MatrixRaw& MatrixRaw){
        
        if(MatrixRaw.empty()){
            throw "setData Error Empty MatrixRaw Data";
        }
       
        data = MatrixRaw;

    }

    void setData(const Matrix& Matrix){
           
        if(Matrix.data.empty()){
            throw "setData Error Empty MatrixRaw Data";
        }
     
        data = Matrix.data;

    }

    MatrixRaw getData(){
        if(data.empty()) throw "getData error data is empty";
        return data; 
    }

    static MatrixRaw Multiply(const Matrix& A, const Matrix& B){
       
        if(A.getColumns() != B.getRows()){
            throw "Matrix size Missmatch";
        }
        MatrixRaw result; 
        vector<double> temprow;
        double temp = 0; 

        for(int row = 0; row < A.getRows(); row++){
            for(int col = 0; col < B.getColumns(); col++){
                for(int x = 0; x < A.getColumns(); x++){
                    temp += A.data[row][x] * B.data[x][col];
                }
                temprow.push_back(temp);
                temp = 0;
            }
            result.push_back(temprow);
            temprow.clear();
            
        }
        return result; 

    }

    static MatrixRaw Multiply(const MatrixRaw& A, const MatrixRaw& B) {

        if(A.empty() || B.empty()) throw "Multiply MatrixRaw empty Matrix";
       
        if(A[0].size() != B.size()){
            throw "Matrix size Missmatch";
        }
        MatrixRaw result; 
        vector<double> temprow;
        double temp = 0; 

        for(int row = 0; row < A.size(); row++){
            for(int col = 0; col < B[0].size(); col++){
                for(int x = 0; x < A[0].size(); x++){
                    temp += A[row][x] * B[x][col];
                }
                temprow.push_back(temp);
                temp = 0;
            }
            result.push_back(temprow);
            temprow.clear();
            
        }
        return result; 

    }


   

//opearator overloadings


    Matrix& operator=(const Matrix& right) {

        if(this == &right) return *this; 

        if(right.data.empty()) throw "operator= error empty Data";

        this->setData(right);
        this->setName(right.getName());
        return *this; 

    }

     Matrix& operator=(const MatrixRaw& right) {

        if(this->data == right) return *this;

        if(right.empty()) throw "operator= error empty Data";

        this->setData(right);
        return *this; 

    }

   friend ostream& operator<<(ostream& out, const Matrix& matrix){ 

        if(matrix.data.empty()){
            out << "No Data in Matrix: "<< matrix.getName() << '\n';
            return out; 
        }

        out << "Name: " << matrix.getName() << endl;
        
        for(int row = 0; row < matrix.getRows(); row ++){
            for(int col = 0; col < matrix.getColumns(); col++){
                out << matrix.data[row][col] << " ";

            }
            out << "\n";
        }
        return out;
    }

    MatrixRaw operator*(const Matrix& other) const {
        return Multiply(data, other.data);
    }


};

Matrix::Matrix(/* args */)
{
    name = "Unnamed"; 
}

Matrix::~Matrix()
{
}



#endif