#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

#include "matrix.h"
using namespace std;


double random(double x){ return (double)(((rand() %10000)+1)/10000)+0.5; }

//double sigmoid(double X){return 1/(1+exp(-X)); }
double upper(double X){ return ceil(X); }
double lower(double X){ return floor(X); }

int main(int argc, char *argv[]){ //C.applyFunc(SP); 
	srand(time(NULL));

	//Initialization
	double Lrate = 2.0;	int nInput = 3;	int nOutput = 2;	int nHidden = 4;


	//THINK of this in terms of a TOP-DOWN Row thingy
	Matrix Input(1,nInput);				Input.fake(1);
	Matrix Weight1(nInput, nHidden);	Weight1.fake(2);
	Matrix Bias1(1,nHidden);			Bias1.fake(3.5);

	Matrix Hidden;
	Matrix Weight2(nHidden, nOutput);	Weight2.fake(4);
	Matrix Bias2(1,nOutput);			Bias2.fake(5.5);
	Matrix Output, IdealOutput(1,nOutput); IdealOutput.fake(0.5);
	///////////////////////////////////////////////////////////////////
	//Calculations of Output and Hidden
	printf("\nInputs:\n");
	Input.print();

	printf("\nWeight 1: \n");
	Weight1.print();

	printf("\nBias 1:\n");
	Bias1.print();

	Matrix inner1 = (Input*Weight1)+Bias1;
	printf("\nInner Product 1\n\n");
	inner1.print();

	Hidden = ((Input*Weight1)+Bias1).applyFunc(upper);
	printf("\nHidden Layer\n\n");
	Hidden.print();

	printf("\nWeight 2: \n");
	Weight2.print();

	printf("\nBias 2:\n");
	Bias2.print();
	Output = ((Hidden*Weight2)+Bias2).applyFunc(upper);

	printf("\nOutput Y\n\n");
	Output.print();

	///////////////////////////////////////////////
	//Calculating gradients
	// ERROR : J = 0.5 * (Ideal Output - Actual Output) ^2

	Matrix dJdB2 = (Output - IdealOutput).hadamard(((Hidden*Weight2)+Bias2).applyFunc(lower));
	printf("\nDJDB2 is : \n\n");
	dJdB2.print();
	Matrix dJdB1 = (dJdB2 * (Weight2.transpose())).hadamard(((Input*Weight1)+Bias1).applyFunc(lower));
	printf("\nDJDB1 is : \n\n");
	dJdB1.print();

	Matrix dJdW2 = Hidden.transpose() * dJdB2;
	printf("\nDJDW2 is : \n\n");
	dJdW2.print();

	Matrix dJdW1 = Input.transpose() * dJdB1;

	printf("\nDJDW1 is : \n\n");
	dJdW1.print();


	//Calculate the new biases
	Matrix newBias2 = Bias2 - (dJdB2 * Lrate);
	printf("\nNew Bias 2 is : \n\n");
	newBias2.print();

	Matrix newBias1 = Bias1 - (dJdB1 * Lrate);
	printf("\nNew Bias 1 is : \n\n");
	newBias1.print();


	Matrix newWeight2 = Weight2 - (dJdW2 * Lrate);
	printf("\nNew Weight 2 is : \n\n");
	newWeight2.print();

	Matrix newWeight1 = Weight1 - (dJdW1 * Lrate);
	printf("\nNew Weight 1 is : \n\n");
	newWeight1.print();












	return 0;
}

