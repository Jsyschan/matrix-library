#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

#include "matrix.h"
#include "nn1.h"
using namespace std;


int main(int argc, char *argv[]){ //C.applyFunc(SP); 
	srand(time(NULL));

	//Initialization
	double Lrate = 2.0;	int nInput = 7;	int nOutput = 2;	int nHidden = 4; int nHiddenL = 3;

	/*
	//Quick Test: 3 'Hidden Layers' of meat
	Matrix *meat;
	meat = (Matrix *) malloc(sizeof(Matrix)*3);
	meat[0] = Matrix(1,3); meat[0].fake(2);
	meat[1] = Matrix(1,5); meat[1].fake(7);
	meat[2] = Matrix(2,6); meat[2].fake(9);
	printf("\n\nBEEF:\n\n"); meat[0].print();
	printf("\n\nPORK:\n\n"); meat[1].print();
	printf("\n\nCHICKEN:\n\n"); meat[2].transpose().print();
	free(meat);
	 */


	Network test1;
	test1.initialize(nInput,nOutput,nHidden,nHiddenL,Lrate);	//test1.print();
	test1.randomize();											test1.print();
	Matrix input(1,nInput); input.fake();					
	printf("\nPrinting INPUT:\n\n");
	input.print(); printf("\n\n");

	//Single Iteration
	Matrix output = test1.iterate(input);
	printf("\nPRINTING OUTPUT\n");
	output.print(); printf("\n\n");




	:wq











	/*
	//THINK of this in terms of a TOP-DOWN Row thingy
	Matrix Input(1,nInput);						Input.fake(1);
	Matrix Weight1(nInput, nHidden);			Weight1.fake(2);
	Matrix Bias1(1,nHidden);					Bias1.fake(3.5);
	Matrix Hidden;
	Matrix Weight2(nHidden, nOutput);			Weight2.fake(4);
	Matrix Bias2(1,nOutput);					Bias2.fake(5.5);
	Matrix Output, IdealOutput(1,nOutput);		IdealOutput.fake(0.5);

	///////////////////////////////////////////////
	//Calculating gradients ERROR : J = 0.5 * (Ideal Output - Actual Output) ^2

	Matrix dJdB2 = (Output - IdealOutput).hadamard(((Hidden*Weight2)+Bias2).applyFunc(lower));
	Matrix dJdB1 = (dJdB2 * (Weight2.transpose())).hadamard(((Input*Weight1)+Bias1).applyFunc(lower));
	Matrix dJdW2 = Hidden.transpose() * dJdB2;
	Matrix dJdW1 = Input.transpose() * dJdB1;

	//Calculate the new biases
	Matrix newBias2 = Bias2 - (dJdB2 * Lrate);
	Matrix newBias1 = Bias1 - (dJdB1 * Lrate);
	Matrix newWeight2 = Weight2 - (dJdW2 * Lrate);
	Matrix newWeight1 = Weight1 - (dJdW1 * Lrate);
	 */








	return 0;
}

