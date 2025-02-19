#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

using namespace std;

class Matrix{
	public:
		//Constructors
		Matrix();					//EMPTY Matrix
		Matrix(int, int);			//Matrix WITH ROW AND COL
<<<<<<< HEAD
		Matrix(const Matrix &);		//Copy Constructor
		//void* operator new(size_t size);		//NEW operator
		~Matrix();					//Destructor
		//void operator delete(void*);//DELETE operator

=======
		Matrix(const Matrix &);
		~Matrix();					//Destructor
>>>>>>> d94244eaa93d259f0091fdf4a5fccc5cb28dd777
		void setRow(int);			//Set the number of Rows --EMPTY MATRIX ONLY
		void setCol(int);			//Set the number of Cols --EMPTY MATRIX ONLY
		
		void operator= (const Matrix &);

		//Matrix operations involving the matrix in question
		double & operator()	(int,int) const;			//Get individual element
		Matrix operator*	(const double &);			//Scalar
		Matrix operator*	(const int &);				//Scalar
		Matrix operator*	(const Matrix &) const;	//Hadamard Product
		Matrix operator->*	(const Matrix &) const;	//Dot Product
		Matrix operator+	(const Matrix &) const;	//Matrix addition
		Matrix operator-	(const Matrix &) const;	//Matrix subtraction
		Matrix transpose	() const;					//Transpose Matrix
		Matrix subRow		(int)		const;	//Return a row of a Matrix
		Matrix subCol		(int)		const;	//Return a col of a Matrix
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
