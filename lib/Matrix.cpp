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

MatrixRaw Identity(int x){
    MatrixRaw Identity(x, vector<double>(x, 0.0));
    for(int i = 0; i < x; i++){
        Identity[i][i] = 1.0;
    }
    return Identity; 
}

MatrixRaw Append(const MatrixRaw& A,const MatrixRaw& B) {
    if(A.empty() || B.empty()) throw "Append Error Matrix empty";
    if(A.size() != B.size()) throw "Append Error Diffrent Row number";

    MatrixRaw result; 
    vector<double> tempRow;
        for(int row = 0; row < A.size(); row++){
            for(int col = 0; col < A[0].size(); col++){
                tempRow.push_back(A[row][col]);
            }
            for(int col = 0; col < B[0].size(); col ++){
                tempRow.push_back(B[row][col]);
            }
            result.push_back(tempRow);
            tempRow.clear();
        }
        return result; 


}

ostream& operator<<(ostream& out, const MatrixRaw& data){ 

    
        
        for(int row = 0; row < data.size(); row ++){
            for(int col = 0; col < data[0].size(); col++){
                out << data[row][col] << " ";

            }
            out << "\n";
        }
        return out;
    }

static void SingleRowScalar(int row, double scale,MatrixRaw& data){

        if(data.empty()) throw "SingleRowScalar error empty matrix";

        for(int col = 0; col < data[row].size(); col++){
            data[row][col] *= scale; 
        }
    }
    // RowB = RowB - (RowA * scale)
static void RowRowAddition(int rowA, int rowB, double scale, MatrixRaw& data){

        if(data.empty()) throw "RowRowSubraction error empty matrix";

        for(int col = 0; col < data[rowA].size(); col++){
            data[rowB][col] += (data[rowA][col] * scale);
        }

    }
    
static void RowSwap(int rowA, int rowB,MatrixRaw& data){
        vector<double> temp;
        temp = data[rowA];
        data[rowA] = data[rowB];
        data[rowB] = temp;
    }

MatrixRaw GaussianJordanElimination(const MatrixRaw& data){
        if(data.empty()) throw "GaussianJordanElimination error emtpy matrix";
    //Created with ChaGPT
       MatrixRaw result = data;

    int rows = result.size();
    int cols = result[0].size();

    int pivotRow = 0;

    for (int pivotCol = 0; pivotCol < cols; pivotCol++) {

        if (pivotRow >= rows)
            break;

        // Find a nonzero pivot
        int swapRow = pivotRow;

        while (swapRow < rows && result[swapRow][pivotCol] == 0) {
            swapRow++;
        }

        // No pivot exists in this column
        if (swapRow == rows)
            continue;

        // Swap rows if necessary
        if (swapRow != pivotRow) {
            RowSwap(pivotRow, swapRow, result);
        }

        // Normalize pivot row
        SingleRowScalar(pivotRow, 1.0 / result[pivotRow][pivotCol], result);

        // Eliminate pivot column from every other row
        for (int row = 0; row < rows; row++) {

            if (row == pivotRow)
                continue;

            RowRowAddition(pivotRow, row, -result[row][pivotCol], result);
        }

        pivotRow++;
    }

    return result;
    // End of AI geneation 
    }


MatrixRaw DetachFront(int ColCuttoff,const MatrixRaw& data){
   
    if(data.empty()) throw "DetachFront error empty data";

    if(data[0].size() < ColCuttoff) throw "DetachFront error invalid Column cuttoff size";
   
   
    MatrixRaw result;
    int totalrows = data.size();
    vector<double> temprow;

        for(int row = 0; row < totalrows; row++){
            for(int col = 0; col < ColCuttoff; col++){
                temprow.push_back(data[row][col]); 
            }
            result.push_back(temprow);
            temprow.clear();
        }
        return result; 
    }

MatrixRaw DetachBack(int colCuttof,const MatrixRaw& data){
    
    if(data.empty()) throw "DetachBack error empy data";

    if(colCuttof > data[0].size()) throw "DetachBack error invalid Column cuttof size";

    MatrixRaw result; 
    int totalrows = data.size();
    int EndCol = data[0].size();
    vector<double> temprow;


    for(int row = 0; row < totalrows; row++){
        for(int col = colCuttof; col < EndCol; col++){
            temprow.push_back(data[row][col]);
        }
        result.push_back(temprow);
        temprow.clear();
    }
    return result;
}

#endif