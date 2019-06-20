#include <assert.h>

#include "matrix.h"

using namespace std;

void Matrix::fake(){

	for(int i=0; i<nrows; i++){
		for(int j=0; j<ncols; j++){
			this->array[i][j] = (i*ncols)+j;
		}
	}
	
	printf("Array 0 0 is %f\n",array[0][0]);
}

//Constructor
Matrix::Matrix(){
	this->array = NULL;
	this->nrows = -1;
	this->ncols = -1;
	this->ncell = 0;
}

//Destructor
Matrix::~Matrix(){
	for(int i=nrows-1; i>=0; i--)
		free(this->array[i]);
	
	free(this->array);
}


//Constructor with row and column arguments
Matrix::Matrix(int row, int col){
	this->nrows = row;
	this->ncols = col;
	this->ncell = row * col;

	//First, create an array of double* for the rows
	this->array = (double **) malloc(sizeof(double *)*row);

	//Next, go through each 'row', and create an array of doubles for the columns
	for(int i=0; i<row; i++)	
		this->array[i] = (double *) malloc(sizeof(double)*col);	
	
}

//Return parameters of this matrix
int Matrix::getNrows() const { return nrows;	}
int Matrix::getNcols() const { return ncols;	}
int Matrix::getNcell() const { return ncell;	}
int Matrix::getIcell(int r,int c) const {return array[r][c]; }

//Constructor when passing along a 'vector' array
Matrix::Matrix(const Matrix &M){
	this->nrows = M.nrows;
	this->ncols = M.ncols;
	this->ncell = M.ncell;

	//First, create an array of double* for the rows
	this->array = (double **) malloc(sizeof(double *)*(this->nrows));

	//Next, go through each 'row', and create an array of doubles for the columns
	for(int i=0; i<(this->nrows); i++){
		this->array[i] = (double *) malloc(sizeof(double)*(this->ncols));	
		for(int j=0; j<(this->ncols); j++){
			this->array[i][j] = M.array[i][j];
		}
	}
}



//Pretty Print, takes into account the space between each element of matrix
void Matrix::print() const {


	printf("\n");
	for(int i=0; i<nrows; i++){
		printf("Row %3d: [",i);
		for(int j=0; j<ncols; j++){
			printf(" %07.3f",array[i][j]);
		}
		printf(" ]\n");
	}

}


Matrix Matrix::mult(int const &value){
	return mult((double)value);
}



Matrix Matrix::mult(double const &value){
	Matrix result(this->nrows,this->ncols);
	int i,j;

	for (i=0 ; i<(this->nrows) ; i++)	
		for (j=0 ; j<(this->ncols) ; j++)		
			result.array[i][j] = this->array[i][j] * value;

	return result;
}


Matrix Matrix::add(Matrix const &m) const{
	assert(nrows==m.nrows && ncols==m.ncols);

	Matrix result(nrows,ncols);
	int i,j;

	for (i=0 ; i<nrows ; i++)
		for (j=0 ; j<ncols ; j++)
			result.array[i][j] = array[i][j] + m.array[i][j];

	return result;
}



Matrix Matrix::sub(Matrix const &m) const{
	assert(nrows==m.nrows && ncols==m.ncols);

	Matrix result(nrows, ncols);
	int i,j;

	for (i=0 ; i<nrows ; i++)
		for (j=0 ; j<ncols ; j++)
			result.array[i][j] = array[i][j] - m.array[i][j];

	return result;
}


Matrix Matrix::hadamard(Matrix const &m) const{
	assert(nrows==m.nrows && ncols==m.ncols);

	Matrix result(nrows, ncols);
	int i,j;

	for (i=0 ; i<nrows ; i++)
		for (j=0 ; j<ncols ; j++)
			result.array[i][j] = array[i][j] * m.array[i][j];

	return result;
}

//Remember: Columns of THIS, and Rows of &m
Matrix Matrix::dot(Matrix const &m) const{
	assert(ncols==m.nrows);

	int i,j,h, mncols = m.ncols;
	double w=0;

	Matrix result(nrows, mncols);

	for (i=0 ; i<nrows ; i++)	{
		for (j=0 ; j<mncols ; j++)		{
			for (h=0 ; h<ncols ; h++)			{
				w += array[i][h]*m.array[h][j];
			}
			result.array[i][j] = w;
			w=0;
		}
	}

	return result;
}


//Element (i,j) becomes (j,i)
Matrix Matrix::transpose() const {
	Matrix result(ncols, nrows);
	int i,j;

	for (i=0 ; i<ncols ; i++){
		for (j=0 ; j<nrows ; j++){
			result.array[i][j] = array[j][i];
		}
	}
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

/*
//Operator Overloading
ostream& operator<<( ostream &flux, Matrix const &m){
	m.print(flux);	return flux;
}
*/
