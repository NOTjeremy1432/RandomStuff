#ifndef Matrix_cpp
#define Matrix_cpp

using namespace std;

#include <vector>
#include <string>

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

    string getName(){
        return name;
    }

    int getRows(){
        if(data.empty()) throw "GetRows Error data is empty";
        return data.size();
    }
    
    int getColumns(){
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

//opearator overloadings
public:

    Matrix& operator=(const Matrix& right) {

        if(this == &right) return *this; 

        if(right.data.empty()) throw "operator= error empty Data";

        this->setData(right);
        return *this; 

    }
     Matrix& operator=(const MatrixRaw& right) {

        if(this->data == right) return *this;

        if(right.empty()) throw "operator= error empty Data";

        this->setData(right);
        return *this; 

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