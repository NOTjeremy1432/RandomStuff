#ifndef Matrix_cpp
#define Matrix_cpp

using namespace std;

#include <vector>
#include <string>


class Matrix
{
private:
    vector<vector<double>> data;
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
        return data.size();
    }
    
    int getColumns(){
        return data[0].size();
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