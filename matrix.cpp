#include <assert.h>

#include "matrix.h"

using namespace std;



//Empty Constructor
Matrix::Matrix(){
	this->array = NULL;
	this->nrows = -1;
	this->ncols = -1;
	this->ncell = 0;
}

//Destructor
Matrix::~Matrix(){
	if(this->array != NULL){
		for(int i=nrows-1; i>=0; i--)		
			free(this->array[i]);	
		free(this->array);
	}
}


//COPY CONSTRUCTOR
Matrix::Matrix(const Matrix &A){
	//printf("Size of A is %d by %d\n",A.nrows,A.ncols);
	this->nrows = A.nrows;
	this->ncols = A.ncols;
	this->array = NULL;


	//First, create an array of double* for the rows
	this->array = (double **) malloc(sizeof(double *)*this->nrows);

	//Next, go through each 'row', create an array of doubles for the cols
	for(int i=0; i<this->nrows; i++){
		this->array[i] = (double *) malloc(sizeof(double)*this->ncols);		
		for(int j=0; j<this->ncols; j++){
			this->array[i][j] = A(i,j);
		}
	}
}




//Constructor with row and column arguments
Matrix::Matrix(int row, int col){
	//Set the number of rows and cols
	this->nrows = row;		this->ncols = col;		this->ncell = row * col;

	//First, create an array of double* for the rows
	this->array = (double **) malloc(sizeof(double *)*row);

	//Next, go through each 'row', create an array of doubles for the cols
	for(int i=0; i<row; i++){
		this->array[i] = (double *) malloc(sizeof(double)*col);		
		for(int j=0; j<col; j++){
			this->array[i][j] = 0.0;
		}
	}
}


//Pretty Print, takes into account the space between each element of matrix
void Matrix::print() const {
	for(int i=0; i<nrows; i++){
		printf("   [ ");
		for(int j=0; j<ncols; j++){			printf("%-7.2f",array[i][j]);		}
		printf(" ]\n");
	}
	printf("\n");
}





////////////////////////////////////////////////////////////////////////////////////////////////

//Given an empty matrix, start to build it up by setting the number of rows:
void Matrix::setRow(int X){
	assert((this->nrows) == -1 && 0 < X);
	this->nrows = X;
	this->array = (double **) malloc(sizeof(double *)*X);
}



//Given an empty matrix, start to build it up by setting the number of cols
//You're assuming here that the rows have already been allocated
void Matrix::setCol(int Y){
	assert((this->nrows) != -1 && (this->nrows) > 0 && 0 < Y && (this->ncols) == -1);
	this->ncols = Y;

	//Next, go through each 'row', create an array of doubles for the cols
	for(int i=0; i<(this->nrows); i++){
		this->array[i] = (double *) malloc(sizeof(double)*Y);		
		for(int j=0; j<Y; j++){
			this->array[i][j] = 0.0;
		}
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////

//Return a reference to (this->array[i][j]) with &
//This way, you can assign a value to it
//Normally, you're returning a temporary object, but with '&',
//you're returning a reference to the actual object
double & Matrix::operator () (int X, int Y) const{
	assert(X < (this->nrows) && 0 <= X && Y < (this->ncols) && 0 <= Y);
	return this->array[X][Y];
}


//When you want to copy a matrix to another Matrix variable
void Matrix::operator= (const Matrix &M) {


	//First, Go through the variable Matrix and free the array
	if(this->array != NULL){
		for(int i=nrows-1; i>=0; i--)	free(this->array[i]);	
		free(this->array);
		this->array = NULL;
	}

	//Using parameters from the matrix being copied, rebuild it
	this->nrows = M.nrows;	this->ncols = M.ncols;	this->ncell = M.ncell;

	//First, create an ariray of double* for the rows
	this->array = (double **) malloc(sizeof(double *)*(this->nrows));

	//Next, go through each 'row', and copy over elements
	for(int i=0; i<(this->nrows); i++){
		this->array[i] = (double *) malloc(sizeof(double)*(this->ncols));	
		for(int j=0; j<(this->ncols); j++){
			this->array[i][j] = M.array[i][j];
		}
	}
	
	//return *this;
}

//Scalar Multiplication
Matrix Matrix::operator*(const double &value){
	Matrix result(this->nrows,this->ncols);
	int i,j;

	for (i=0 ; i<(this->nrows) ; i++)	
		for (j=0 ; j<(this->ncols) ; j++)		
			result.array[i][j] = this->array[i][j] * value;

	return result;
}

//Scalar Multiplication
Matrix Matrix::operator* (const int &value){
	Matrix result(this->nrows,this->ncols);
	int i,j;

	for (i=0 ; i<(this->nrows) ; i++)	
		for (j=0 ; j<(this->ncols) ; j++)		
			result.array[i][j] = this->array[i][j] * (double) value;

	return result;
}

//Remember: Columns of THIS, and Rows of &m
//Matrix multiplication: DOT PRODUCT
Matrix Matrix::operator->* (const Matrix &m) const{
	assert(ncols==m.nrows);
	int i,j,h, mncols = m.ncols;	double w=0;
	Matrix result(nrows, mncols);

	for (i=0 ; i<nrows ; i++)	{
		for (j=0 ; j<mncols ; j++)		{
			for (h=0 ; h<ncols ; h++)			
				w += array[i][h]*m.array[h][j];
			result.array[i][j] = w;
			w=0;
		}
	}
	return result;
}

//Matrix Addition
Matrix Matrix::operator+ (const Matrix &m) const{
	assert(nrows==m.nrows && ncols==m.ncols);
	Matrix result(nrows,ncols);		int i,j;

	for (i=0 ; i<nrows ; i++)
		for (j=0 ; j<ncols ; j++)
			result.array[i][j] = array[i][j] + m.array[i][j];

	return result;
}

//Matrix Subtraction
Matrix Matrix::operator- (const Matrix &m) const{
	assert(nrows==m.nrows && ncols==m.ncols);
	Matrix result(nrows, ncols);	int i,j;

	for (i=0 ; i<nrows ; i++)
		for (j=0 ; j<ncols ; j++)
			result.array[i][j] = array[i][j] - m.array[i][j];

	return result;
}

//Matrix Transposition
//Element (i,j) becomes (j,i)
Matrix Matrix::transpose() const {
	Matrix result(ncols, nrows);	int i,j;

	for (i=0 ; i<ncols ; i++)
		for (j=0 ; j<nrows ; j++)
			result.array[i][j] = array[j][i];

	return result;
}


//Matrix Multiplcation: Element-wise, not matrix wise
Matrix Matrix::operator* (const Matrix &m) const{
	assert(nrows==m.nrows && ncols==m.ncols);
	Matrix result(nrows, ncols);	int i,j;

	for (i=0 ; i<nrows ; i++)
		for (j=0 ; j<ncols ; j++)
			result.array[i][j] = array[i][j] * m.array[i][j];

	return result;
}


//Use this function to get a row of a matrix
Matrix Matrix::subRow(int R) const {
	assert(R>=0 && R < (this->nrows));
	Matrix result(1,this->ncols);
	for (int j=0 ; j<(this->ncols) ; j++)	result.array[0][j] = this->array[R][j];
	return result;
}








//Use this function to get a column of a matrix
Matrix Matrix::subCol(int R) const {
	assert(R>=0 && R < (this->ncols));
	Matrix result(this->nrows,1);
	for (int j=0 ; j<(this->nrows) ; j++)	result.array[j][0] = this->array[j][R];
	return result;
}













// Takes as parameter a function which prototype looks like : double function(double x)
Matrix Matrix::applyFunc(double (*function)(double)) const{
	Matrix result(nrows, ncols);
	int i,j;

	for (i=0 ; i<nrows ; i++)	{
		for (j=0 ; j<ncols ; j++){
			result.array[i][j] = (*function)(array[i][j]);
		}
	}

	return result;
}










