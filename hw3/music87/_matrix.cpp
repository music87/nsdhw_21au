#include<iostream>
#include<sys/time.h>
#include<cstdlib>
#include<time.h>
#include<cassert>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<mkl.h>
#include<pybind11/pybind11.h>
#include<pybind11/operators.h>
#include<pybind11/stl.h>

class Matrix2D{
    friend Matrix2D multiply_mkl(Matrix2D const & mat1, Matrix2D const & mat2);
public:
    // constructor
    Matrix2D() : dnrow(0), dncol(0) {};
    Matrix2D(size_t nrow, size_t ncol);
    Matrix2D(Matrix2D const &other);// copy constructor
    Matrix2D(Matrix2D && other);// move constructor, && means rvalue
    
    // destructor
    ~Matrix2D();
    
    // operator
    Matrix2D & operator=(Matrix2D const & other); // copy assignment operator
    Matrix2D & operator=(Matrix2D && other); // move assignment operator
    double & operator()(size_t row, size_t col); // indexing operator for ordinary Matrix2D
    double & operator()(size_t row, size_t col) const; // indexing operator for const Matrix2D
        
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

std::ostream & operator << (std::ostream & ostr, Matrix2D const & mat)
{
    for (size_t i=0; i<mat.nrow(); ++i) // the i-th row
    {
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j) // the j-th column
        {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }

    return ostr;
}

std::ostream & operator << (std::ostream & ostr, std::vector<double> const & vec)
{
    for (size_t i=0; i<vec.size(); ++i)
    {
        std::cout << " " << vec[i];
    }

    return ostr;
}

Matrix2D::Matrix2D(size_t nrow, size_t ncol) : dnrow(nrow), dncol(ncol){
    size_t nelement = nrow * ncol;
    dbuffer = new double[nelement];
    for(size_t i=0; i<nelement; i++){
        dbuffer[i]=0;
    }
}

Matrix2D::~Matrix2D(){
    delete[] dbuffer;
}

Matrix2D::Matrix2D(Matrix2D const& other){
    // copy constructor
    dnrow = other.dnrow;
    dncol = other.dncol;
    size_t nelement = other.dnrow*other.dncol;
    if(dbuffer)
        delete[] dbuffer;
    dbuffer = new double[nelement];
    std::copy_n(other.dbuffer, other.dncol*other.dnrow, dbuffer);
}

Matrix2D::Matrix2D(Matrix2D &&other){
    // move constructor
    std::swap(dnrow, other.dnrow);
    std::swap(dncol, other.dncol);
    std::swap(dbuffer, other.dbuffer);
}

Matrix2D& Matrix2D::operator=(Matrix2D const &other){
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

Matrix2D& Matrix2D::operator=(Matrix2D && other){
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

double& Matrix2D::operator()(size_t row, size_t col){
    // indexing operator
    if(row*col > dnrow*dncol)
        throw std::invalid_argument("index exceed the matrix bound");
    return dbuffer[row*dncol + col];
}

double& Matrix2D::operator()(size_t row, size_t col) const{
    // indexing operator
    if(row*col > dnrow*dncol)
        throw std::invalid_argument("index exceed the matrix bound");
    return dbuffer[row*dncol + col];
}

bool operator==(Matrix2D const & mat1, Matrix2D const & mat2)
{
    if ((mat1.ncol() != mat2.ncol()) && (mat1.nrow() != mat2.ncol()))
    {
        return false;
    }

    for (size_t i=0; i<mat1.nrow(); ++i)
    {
        for (size_t j=0; j<mat1.ncol(); ++j)
        {
            if (mat1(i, j) != mat2(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

size_t Matrix2D::nrow() const {
    // const after declaration means that this member function won't change any member variables in the class
    return dnrow;
}

size_t Matrix2D::ncol() const {
    return dncol;
}

double* Matrix2D::buffer() const{
	return dbuffer;
}

void Matrix2D::printself() const{
    for (size_t i=0; i<this->nrow(); ++i) // the i-th row
    {
        std::cout << std::endl << " ";
        for (size_t j=0; j<this->ncol(); ++j) // the j-th column
        {
	    std::cout << " " << std::setw(2) << dbuffer[i*ncol()+j];
        }
    }
    std::cout << std::endl;
}

Matrix2D multiply_naive(Matrix2D const &mat1, Matrix2D const &mat2){
    if(mat1.ncol() != mat2.nrow())
        throw std::invalid_argument("matrix1's number of columns isn't equal to matrix2's number of rows");
    Matrix2D res(mat1.nrow(), mat2.ncol());
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


Matrix2D multiply_tile(Matrix2D const &mat1, Matrix2D const &mat2, const size_t block_size){
    Matrix2D res(mat1.nrow(), mat2.ncol());
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

Matrix2D multiply_mkl(Matrix2D const &mat1, Matrix2D const &mat2){
    //mkl_set_num_threads(1);
    Matrix2D res(mat1.nrow(), mat2.ncol());
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
       , res.dbuffer
       , res.ncol()
     );
    return res;
}

PYBIND11_MODULE(_matrix, m){
    m.doc() = "matrix matrix multiplication";
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
    
    pybind11::class_<Matrix2D>(m,"Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def("__getitem__", [](Matrix2D &m, std::pair<size_t, size_t> idx) {
                    return m(idx.first, idx.second);
        })
        .def("__setitem__", [](Matrix2D &m, std::pair<size_t, size_t> idx, double value) {
                    m(idx.first, idx.second) = value;
                })
        .def_property_readonly("nrow", &Matrix2D::nrow)
        .def_property_readonly("ncol", &Matrix2D::ncol)
	.def("printself", &Matrix2D::printself)
        .def(pybind11::self == pybind11::self);

}

/*
void initialize(Matrix2D & mat){
    for (size_t i=0; i<mat.nrow(); ++i)
        for (size_t j=0; j<mat.ncol(); ++j)
                mat(i, j) = rand()%100;
}
int main(){
	srand( time(NULL) );
	size_t mat_size = 1000;
	Matrix2D m1(mat_size, mat_size);
	initialize(m1);
	Matrix2D m2=m1;
	
	clock_t tic = clock();
	Matrix2D res_ans = multiply_mkl(m1,m2);
	clock_t toc = clock();
	double time_ans = (double)(toc - tic) / CLOCKS_PER_SEC;
	std::cout << time_ans << "(s), ans" << std::endl;

	tic = clock();
	Matrix2D res_tile = multiply_tile(m1,m2,128);
	toc = clock();
	double time_tile = (double)(toc - tic) / CLOCKS_PER_SEC;
	std::cout << time_tile << "(s), tile" << std::endl;

	tic = clock();
	Matrix2D res_naive = multiply_naive(m1,m2);
	toc = clock();
	double time_naive = (double)(toc - tic) / CLOCKS_PER_SEC;
	std::cout << time_naive << "(s), naive" << std::endl;

	
	//std::cout << "matrix1:" << m1 << std::endl;
	//std::cout << "matrix2:" << m2 << std::endl;
	
	//std::cout << "ans:" << std::endl;
	//std::cout << "naive:" << std::endl;
	//std::cout << "tile:" << std::endl;
	
	assert(res_ans == res_naive);
	assert(res_ans == res_tile);
	return 0;
}*/
