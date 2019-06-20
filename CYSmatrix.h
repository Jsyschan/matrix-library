##This is from 'Cause You're Stuck' about Neural Networks from scratch

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <iostream>

using namespace std;

class Matrix
{
	public:
		Matrix();
		Matrix(int height, int width);
		Matrix(vector<vector<double> > const &array);

		Matrix multiply(double const &value); // scalar multiplication

		Matrix add(Matrix const &m) const; // addition
		Matrix subtract(Matrix const &m) const; // subtraction
		Matrix multiply(Matrix const &m) const; // hadamard product

		Matrix dot(Matrix const &m) const; // dot product
		Matrix transpose() const; // transposed matrix

		Matrix applyFunction(double (*function)(double)) const; // to apply a function to every element of the matrix

		void print(ostream &flux) const; // pretty print of the matrix

	private:
		vector<vector<double>> array;
		int height;
		int width;
};

ostream& operator<<(ostream &flux, Matrix const &m); // overloading << operator to print easily

#endif
