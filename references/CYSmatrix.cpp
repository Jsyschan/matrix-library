This is from Cause You're Stuck about NN scratch practice

#include <assert.h>
#include <sstream>

#include "matrix.h"

using namespace std;

//Constructor
Matrix::Matrix(){}

//Constructor with arguments
Matrix::Matrix(int height, int width){
	this->height = height;
	this->width = width;
	this->array =  vector< vector<double> >(height,  vector<double>(width));
}

//Constructor when passing along a 'vector' array
Matrix::Matrix( vector< vector<double> > const &array){
	assert(array.size()!=0);
	this->height = array.size();
	this->width = array[0].size();
	this->array = array;
}

Matrix Matrix::multiply(double const &value){
	Matrix result(height, width);
	int i,j;

	for (i=0 ; i<height ; i++)	
		for (j=0 ; j<width ; j++)		
			result.array[i][j] = array[i][j] * value;

	return result;
}

Matrix Matrix::add(Matrix const &m) const{
	assert(height==m.height && width==m.width);

	Matrix result(height, width);
	int i,j;

	for (i=0 ; i<height ; i++)
		for (j=0 ; j<width ; j++)
			result.array[i][j] = array[i][j] + m.array[i][j];

	return result;
}

Matrix Matrix::subtract(Matrix const &m) const{
	assert(height==m.height && width==m.width);

	Matrix result(height, width);
	int i,j;

	for (i=0 ; i<height ; i++)
		for (j=0 ; j<width ; j++)
			result.array[i][j] = array[i][j] - m.array[i][j];

	return result;
}

Matrix Matrix::multiply(Matrix const &m) const{
	assert(height==m.height && width==m.width);

	Matrix result(height, width);
	int i,j;

	for (i=0 ; i<height ; i++)
		for (j=0 ; j<width ; j++)
			result.array[i][j] = array[i][j] * m.array[i][j];

	return result;
}

Matrix Matrix::dot(Matrix const &m) const{
	assert(width==m.height);

	int i,j,h, mwidth = m.width;
	double w=0;

	Matrix result(height, mwidth);

	for (i=0 ; i<height ; i++)	{
		for (j=0 ; j<mwidth ; j++)		{
			for (h=0 ; h<width ; h++)			{
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
	Matrix result(width, height);
	int i,j;

	for (i=0 ; i<width ; i++){
		for (j=0 ; j<height ; j++){
			result.array[i][j] = array[j][i];
		}
	}
	return result;
}
// Takes as parameter a function which prototype looks like : double function(double x)
Matrix Matrix::applyFunction(double (*function)(double)) const{
	Matrix result(height, width);
	int i,j;

	for (i=0 ; i<height ; i++)	{
		for (j=0 ; j<width ; j++){
			result.array[i][j] = (*function)(array[i][j]);
		}
	}

	return result;
}

//Pretty Print, takes into account the space between each element of matrix
void Matrix::print( ostream &flux) const {
	int i,j;
	int maxLength[width] = {};
	stringstream ss;

	for (i=0 ; i<height ; i++)
	{
		for (j=0 ; j<width ; j++)
		{
			ss << array[i][j];
			if(maxLength[j] < ss.str().size())
			{
				maxLength[j] = ss.str().size();
			}
			ss.str( string());
		}
	}

	for (i=0 ; i<height ; i++)	{
		for (j=0 ; j<width ; j++)		{
			flux << array[i][j];
			ss << array[i][j];
			for (int k=0 ; k<maxLength[j]-ss.str().size()+1 ; k++)	{	flux << " ";	}
			ss.str( string());
		}
		flux <<  endl;
	}
}

//Operator Overloading
ostream& operator<<( ostream &flux, Matrix const &m){
	m.print(flux);	return flux;
}
