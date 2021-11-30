#include<iostream>
#include<sys/time.h>
#include<cstdlib>
#include<time.h>
#include<cassert>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<mkl.h>
#include<functional>
//#include<pybind11/pybind11.h> // we should remove all the pybind header
//#include<pybind11/operators.h> 
//#include<pybind11/stl.h> 

class Matrix{
public:
    // constructor
    Matrix() : dnrow(0), dncol(0) {};
    Matrix(size_t nrow, size_t ncol);
    Matrix(Matrix const &other);// copy constructor
    Matrix(Matrix && other);// move constructor, && means rvalue
    
    // destructor
    ~Matrix();
    
    // operator
    Matrix & operator=(Matrix const & other); // copy assignment operator
    Matrix & operator=(Matrix && other); // move assignment operator
    double & operator()(size_t row, size_t col); // indexing operator for ordinary Matrix
    double & operator()(size_t row, size_t col) const; // indexing operator for const Matrix
        
    // self-defined function
    size_t nrow() const;
    size_t ncol() const;
    double* buffer() const;
    std::vector<double> buffer_vector() const { return std::vector<double>(dbuffer, dbuffer+dnrow*dncol); }
    void printself() const;
private:
    size_t dnrow, dncol;
    double *dbuffer = nullptr;
};

std::ostream & operator << (std::ostream & ostr, Matrix const & mat){
    for (size_t i=0; i<mat.nrow(); ++i){
	// the i-th row
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j){
	// the j-th column
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }
    return ostr;
}

std::ostream & operator << (std::ostream & ostr, std::vector<double> const & vec){
    for (size_t i=0; i<vec.size(); ++i){
        std::cout << " " << vec[i];
    }
    return ostr;
}

Matrix::Matrix(size_t nrow, size_t ncol) : dnrow(nrow), dncol(ncol){
    size_t nelement = nrow * ncol;
    dbuffer = new double[nelement];
    for(size_t i=0; i<nelement; i++){
        dbuffer[i]=0;
    }
}

Matrix::~Matrix(){
    delete[] dbuffer;
}

Matrix::Matrix(Matrix const& other){
    // copy constructor
    dnrow = other.dnrow;
    dncol = other.dncol;
    size_t nelement = other.dnrow*other.dncol;
    if(dbuffer)
        delete[] dbuffer;
    dbuffer = new double[nelement];
    std::copy_n(other.dbuffer, other.dncol*other.dnrow, dbuffer);
}

Matrix::Matrix(Matrix &&other){
    // move constructor
    std::swap(dnrow, other.dnrow);
    std::swap(dncol, other.dncol);
    std::swap(dbuffer, other.dbuffer);
}

Matrix& Matrix::operator=(Matrix const &other){
    // copy assignment operator
    if(&other == this)
        return *this;
    // same as copy constructor
    dnrow = other.dnrow;
    dncol = other.dncol;
    size_t nelement = other.dnrow*other.dncol;
    if(dbuffer)
        delete[] dbuffer;
    dbuffer = new double[nelement];
    std::copy_n(other.dbuffer, other.dncol*other.dnrow, dbuffer);
    // return
    return *this;
}

Matrix& Matrix::operator=(Matrix && other){
    // move assignment operator
    if(&other == this)
        return *this;
    // same as move constructor
    std::swap(dnrow, other.dnrow);
    std::swap(dncol, other.dncol);
    std::swap(dbuffer, other.dbuffer);
    // return
    return *this;
}

double& Matrix::operator()(size_t row, size_t col){
    // indexing operator
    return dbuffer[row*dncol + col];
}

double& Matrix::operator()(size_t row, size_t col) const{
    // indexing operator
    return dbuffer[row*dncol + col];
}

bool operator==(Matrix const & mat1, Matrix const & mat2){
    if ((mat1.ncol() != mat2.ncol()) && (mat1.nrow() != mat2.ncol())){
        return false;
    }

    for (size_t i=0; i<mat1.nrow(); ++i){
        for (size_t j=0; j<mat1.ncol(); ++j){
            if (mat1(i, j) != mat2(i, j)){
                return false;
            }
        }
    }
    return true;
}

size_t Matrix::nrow() const {
    // const after declaration means that this member function won't change any member variables in the class
    return dnrow;
}

size_t Matrix::ncol() const {
    return dncol;
}

double* Matrix::buffer() const{
	return dbuffer;
}

void Matrix::printself() const{
    for (size_t i=0; i<this->nrow(); ++i){
	// the i-th row
        std::cout << std::endl << " ";
        for (size_t j=0; j<this->ncol(); ++j){
            // the j-th column
	    std::cout << " " << std::setw(2) << dbuffer[i*ncol()+j];
        }
    }
    std::cout << std::endl;
}

Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2){
    if(mat1.ncol() != mat2.nrow())
        throw std::invalid_argument("matrix1's number of columns isn't equal to matrix2's number of rows");
    Matrix res(mat1.nrow(), mat2.ncol());
    for(size_t r=0; r<mat1.nrow(); r++){
        for(size_t c=0; c<mat2.ncol(); c++){
            res(r,c)=0; // call ordinary indexing operator
            for(size_t k=0; k<mat1.ncol(); k++){
                // right side of equation call const indexing operator
                // left side of equation call ordinary indexing operator
                res(r,c) += mat1(r,k) * mat2(k,c);
            }
        }
    }
    return res;
}


Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, const size_t block_size){
    Matrix res(mat1.nrow(), mat2.ncol());
    if(mat1.ncol() != mat2.nrow())
        throw std::invalid_argument("matrix1's number of columns isn't equal to matrix2's number of rows");
    
    // https://stackoverflow.com/questions/26892504/c-performacne-analysis-of-tiled-matrix-multiplication-with-valgrind
    // https://penny-xu.github.io/blog/tiled-matrix-multiplication
    for(size_t br=0; br<mat1.nrow(); br+=block_size){
	size_t brlimit = std::min(br+block_size, mat1.nrow());
        for(size_t bc=0; bc<mat2.ncol(); bc+=block_size){
	    size_t bclimit = std::min(bc+block_size,mat2.ncol());
            for(size_t bk=0; bk<mat1.ncol(); bk+=block_size){
                // block matrix multiplication
		size_t bklimit = std::min(bk+block_size, mat1.ncol());
	        for(size_t k=bk; k<bklimit;k++){
		    for(size_t r=br;r<brlimit;r++){
                        for(size_t c=bc;c<bclimit;c++){
                            res(r,c) +=mat1(r,k)*mat2(k,c);
                        }
                    }
                }
            }
        }
    }
    return res;
}

Matrix multiply_mkl(Matrix const &mat1, Matrix const &mat2){
    //mkl_set_num_threads(1);
    Matrix res(mat1.nrow(), mat2.ncol());
    cblas_dgemm(
         CblasRowMajor
       , CblasNoTrans
       , CblasNoTrans
       , mat1.nrow()
       , mat2.ncol()
       , mat1.ncol() 
       , 1.0
       , mat1.buffer()
       , mat1.ncol()
       , mat2.buffer()
       , mat2.ncol()
       , 0.0
       , res.buffer()
       , res.ncol()
     );
    return res;
}

