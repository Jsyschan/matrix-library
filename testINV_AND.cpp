#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

#include "matrix.h"
using namespace std;


double random(double x){ return (double)(((rand() %10000)+1)/10000)+0.5; }

double sigmoid(double X){return 1/(1+exp(-X)); }
double dsigmoid(double X){ return exp(-X) / (pow(1+exp(-X), 2)); }

int main(int argc, char *argv[]){ //C.applyFunc(SP); 
	srand(time(NULL));

	//Initialization
	double Lrate = 0.7;	int nInput = 2;	int nOutput = 2;	int nHidden = 4;
	int nInt = 100;


	Matrix AND1(1,2);		AND1.fill(0,0,(double) 0);			AND1.fill(0,1,(double) 0);
	Matrix AND2(1,2);		AND2.fill(0,0,(double) 0);			AND2.fill(0,1,(double) 1);
	Matrix AND3(1,2);		AND3.fill(0,0,(double) 1);			AND3.fill(0,1,(double) 0);
	Matrix AND4(1,2);		AND4.fill(0,0,(double) 1);			AND4.fill(0,1,(double) 1);

	Matrix OUT1(1,2);		OUT1.fill(0,0,(double) 0);			OUT1.fill(0,1,(double) 1);
	Matrix OUT2(1,2);		OUT2.fill(0,0,(double) 0);			OUT2.fill(0,1,(double) 1);
	Matrix OUT3(1,2);		OUT3.fill(0,0,(double) 0);			OUT3.fill(0,1,(double) 1);
	Matrix OUT4(1,2);		OUT4.fill(0,0,(double) 1);			OUT4.fill(0,1,(double) 0);

	//printf("AND1\n");	AND1.print();
	//printf("AND2\n");	AND2.print();
	//printf("AND3\n");	AND3.print();
	//printf("AND4\n");	AND4.print();
	//printf("OUT1\n");	OUT1.print();
	//printf("OUT2\n");	OUT2.print();
	//printf("OUT3\n");	OUT3.print();
	//printf("OUT4\n");	OUT4.print();
	//THINK of this in terms of a TOP-DOWN Row thingy
	Matrix Input(1,nInput);				Input.fake(1);
	Matrix Weight1(nInput, nHidden);	Weight1.fake(2);
	Matrix Bias1(1,nHidden);			Bias1.fake(3.5);

	Matrix Hidden;
	Matrix Weight2(nHidden, nOutput);	Weight2.fake(4);
	Matrix Bias2(1,nOutput);			Bias2.fake(5.5);
	Matrix Output, IdealOutput(1,nOutput); IdealOutput.fake(0.5);


	while(nInt != 100){

		/////////////////Calculations of Output and Hidden

		Matrix inner1 = (Input*Weight1)+Bias1;
		Hidden = ((Input*Weight1)+Bias1).applyFunc(sigmoid);
		Output = ((Hidden*Weight2)+Bias2).applyFunc(sigmoid);

		///////////////////////////////////////////////
		//Calculating gradients		 ERROR : J = 0.5 * (Ideal Output - Actual Output) ^2

		Matrix dJdB2 = (Output - IdealOutput).hadamard(((Hidden*Weight2)+Bias2).applyFunc(dsigmoid));
		Matrix dJdB1 = (dJdB2 * (Weight2.transpose())).hadamard(((Input*Weight1)+Bias1).applyFunc(dsigmoid));
		Matrix dJdW2 = Hidden.transpose() * dJdB2;
		Matrix dJdW1 = Input.transpose() * dJdB1;

		//Calculate the new biases
		Matrix newBias2 = Bias2 - (dJdB2 * Lrate);
		Matrix newBias1 = Bias1 - (dJdB1 * Lrate);
		Matrix newWeight2 = Weight2 - (dJdW2 * Lrate);
		Matrix newWeight1 = Weight1 - (dJdW1 * Lrate);

		nInt++;
	}










	return 0;
}

