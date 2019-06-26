#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

#include "matrix.h"
#include "nn1.h"

using namespace std;

//double random(double x){ return (double)(((rand() %10000)+1)/10000)+0.5; }
//double sigmoid(double X){return 1/(1+exp(-X)); }
//double dsigmoid(double X){ return exp(-X) / (pow(1+exp(-X), 2)); }

int main(int argc, char *argv[]){ //C.applyFunc(SP); 
	srand(time(NULL));


	printf("\n\nCreating TEMP matrix\n");
	Matrix tmp1(1,3);
	tmp1.fake1();
	printf("\n\nPRINTING TEMP\n\n");
	tmp1.print();

	printf("\n\nCreating IDEAL\n\n");
	Matrix ideal = tmp1; //THIS IS THE PROBLEM RIGHT HERE!!!
	printf("\n\nPRINTING IDEAL\n\n");
	ideal.print();
	



	return 0;
}

