#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

#include "matrix.h"
#include "nn1.h"

using namespace std;

int main(int argc, char *argv[]){ 
	srand(time(NULL));

	//Initialization
	double learn = 0.5;	int n_IN = 2;	int n_OUT = 2;	int l_HID = 4; int nInt = 10000;

	//Simple 2 layer
	dll_head hlist;
	for(int i=0; i<l_HID; i++)	hlist.insert(10);

	Network TNN;
	TNN.initialize(n_IN, n_OUT, l_HID, &hlist, learn);
	TNN.randomize();

	//ROW MATRICES: Let A = col 0, B = col 1
	Matrix inputs(4,n_IN);
	inputs(0,0) = 0;	inputs(0,1) = 0;
	inputs(1,0) = 0;	inputs(1,1) = 1;
	inputs(2,0) = 1;	inputs(2,1) = 0;
	inputs(3,0) = 1;	inputs(3,1) = 1;

	//ROW MATRICES: Let col0 = normal OUTPUT, col1 = INV AND output
	Matrix outputs = inputs;
	outputs(0,0) = 0;	outputs(0,1) = 1;
	outputs(1,0) = 1;	outputs(1,1) = 0;
	outputs(2,0) = 1;	outputs(2,1) = 0;
	outputs(3,0) = 1;	outputs(3,1) = 0;

	Matrix IN, IDEAL, output;
	int index;
	for(int i=0; i<nInt; i++){
		index = rand() % 4;
		IN = inputs.subRow(index);
		IDEAL = outputs.subRow(index);

		output = TNN.iterate(IN);
		TNN.back_prop(IN,output,IDEAL);
	}


	printf("--------------------------------------\n");
	printf("FINAL TEST\n\n");
	for(int i=0; i<4; i++){
		printf("\n\nINPUT %d:\n",i); 
		IN = inputs.subRow(i); 
		IN.print();
		output = TNN.iterate(IN);
		printf("OUTPUT:\n");
		output.print();
	}


	return 0;
}

