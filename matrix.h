#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

using namespace std;

class Matrix{
	public:
			void fake();
			void fake(int);
			void fake(double);
			void fill(int,int,double);
		//Constructors
		Matrix();					//EMPTY Matrix
		Matrix(int, int);			//Matrix WITH ROW AND COL
		~Matrix();					//Destructor
		void operator= (const Matrix &);

		//Matrix operations involving the matrix in question
		Matrix operator* (const double &);			//Scalar
		Matrix operator* (const int &);				//Scalar
		Matrix operator* (const Matrix &) const;	//Dot Product
		Matrix operator+ (const Matrix &) const;	//Matrix addition
		Matrix operator- (const Matrix &) const;	//Matrix subtraction
		Matrix hadamard  (const Matrix &) const;	//Hadamard Product
		Matrix transpose() const;					//Transpose Matrix

		//Basic operations
		int getRows(){ return nrows; }
		int getCols(){ return ncols; }
		void print() const;									// pretty print of the Matrix
		Matrix applyFunc(double (*function)(double)) const; //Apply a function to every element of a Matrix
	private:
		double **array;	//vector<vector<double>> array;
		int nrows;
		int ncols;
		int ncell;
};


#endif
