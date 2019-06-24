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
	//printf("DESTROY: Nrows is %d\tNcols is %d\n",nrows,ncols);
	for(int i=nrows-1; i>=0; i--){
		//for(int j=ncols-1; j>=0; j--)
		//	free(this->array[i][j]);	
		//printf("Freeing array[%d]\n",i);
		free(this->array[i]);
	}

	//printf("Now freeing ptr free\n");
	free(this->array);
}


//Constructor with row and column arguments
Matrix::Matrix(int row, int col){
	this->nrows = row;		this->ncols = col;		this->ncell = row * col;

	//First, create an array of double* for the rows
	this->array = (double **) malloc(sizeof(double *)*row);

	//Next, go through each 'row', and create an array of doubles for the columns -- Maybe initialize to 0s?
	for(int i=0; i<row; i++){
		this->array[i] = (double *) malloc(sizeof(double)*col);		
		for(int j=0; j<col; j++){
			//this->array[i][j] = (double) malloc(sizeof(double)*1);
			this->array[i][j] = (double ) 0;
		}
	}
	//printf("LEAVING CONSTRUCTOR\n");
}


//Pretty Print, takes into account the space between each element of matrix
void Matrix::print() const {
	printf("Size is %d by %d\t\n",nrows,ncols);
	for(int i=0; i<nrows; i++){
		printf("Row %3d: [",i);
		for(int j=0; j<ncols; j++){			printf(" %07.3f",array[i][j]);		}
		printf(" ]\n");
	}
	printf("Leaving PRINT OP\n");
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
			//this->array[i][j] = (double) malloc(sizeof(double)*1);
			this->array[i][j] = M.array[i][j];
		}
	}
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
Matrix Matrix::operator* (const Matrix &m) const{
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
Matrix Matrix::hadamard(const Matrix &m) const{
	assert(nrows==m.nrows && ncols==m.ncols);
	Matrix result(nrows, ncols);	int i,j;

	for (i=0 ; i<nrows ; i++)
		for (j=0 ; j<ncols ; j++)
			result.array[i][j] = array[i][j] * m.array[i][j];

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






















//void Matrix::fill(int X, int Y, double V){	this->array[X][Y] = V;}
void Matrix::fake1() {
	for(int i=0; i<nrows; i++)
		for(int j=0; j<ncols; j++)
			this->array[i][j] = ((i*ncols)+j)+1;	
}
void Matrix::fake2(){
	for(int i=0; i<nrows; i++)
		for(int j=0; j<ncols; j++)
			this->array[i][j] =  (random()*1000) % 7; //input;
}
//void Matrix::fake(int input){
//	for(int i=0; i<nrows; i++)
//		for(int j=0; j<ncols; j++)
//			this->array[i][j] = random() % 100; //(double) input;	
//}





