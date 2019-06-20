#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

using namespace std;

class Matrix{
	public:
		void fake();
		//Constructors
		Matrix();					//EMPTY Matrix
		Matrix(int, int);			//Matrix WITH ROW AND COL
		Matrix(const Matrix &);		//Copy a matrix to this one
		~Matrix();					//Destructor

		//Matrix operations involving the matrix in question
		Matrix mult(int const &);			// scalar multiplication for integers
		Matrix mult(double const &);		// scalar multiplication for doubles
		Matrix add(Matrix const &m) const;	// Matrix addition 
		Matrix sub(Matrix const &m) const;	// Matrix subtraction
		Matrix hadamard(Matrix const &m) const; // hadamard product
		Matrix dot(Matrix const &m) const; // dot product
		Matrix transpose() const;			// transposed Matrix

		//Basic operations
		int getNrows() const;
		int getNcols() const;
		int getNcell() const;
		int getIcell(int,int) const;
		void print() const; // pretty print of the Matrix
		Matrix applyFunc(double (*function)(double)) const; //Apply a function to every element of the Matrix
	private:
		double **array;	//vector<vector<double>> array;
		int nrows;
		int ncols;
		int ncell;
};


#endif
