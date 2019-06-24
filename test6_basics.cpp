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

	//Initialization
	double learn = 0.7;	int n_IN = 2;	int n_OUT = 3;	int l_HID = 2; int nInt = 100;

	//Simple 2 layer
	struct hlist *n_HID, *pn_HID;
	n_HID = (struct hlist *) malloc(sizeof(struct hlist));
	pn_HID = n_HID; 
	pn_HID->next = NULL;	pn_HID->H = 4; pn_HID->prev = NULL;
	pn_HID->next = (struct hlist *) malloc(sizeof(struct hlist));
	pn_HID->next->prev = pn_HID;
	pn_HID = pn_HID->next;
	pn_HID->next = NULL;	pn_HID->H = 5;

	Network TNN;
	TNN.initialize(n_IN, n_OUT, l_HID, n_HID, learn);
	TNN.print();


	printf("\n\nINPUT \n\n");
	Matrix input(1,n_IN);
	input.fake1();
	input.print();



	printf("\n\n\nINPUT ITERATING!\n\n");
	Matrix output = TNN.iterate(input);

	printf("\n\nOUTPUT:\n\n");
	output.print();

	printf("\n\nCreating TEMP matrix\n");
	Matrix tmp1(1,3);
	tmp1.fake1();


	printf("\n\nCreating IDEAL\n\n");
	//Matrix ideal = output; //THIS IS THE PROBLEM RIGHT HERE!!!
	Matrix ideal; 
	ideal = (output - tmp1) ;
	
	printf("\n\nIDEAL OUTPUT:\n\n");
	ideal.print();

	printf("\n\n\n");
	
	printf("\n\nStarting Back Prop\n\n");
	TNN.back_prop(input,output,ideal);
	
	
	
	printf("\n\nTHE END!\n\n");




	
	//Be sure to write a better 'free function' here
	pn_HID = n_HID;
	while(pn_HID->next != NULL) pn_HID = pn_HID->next;

	while(pn_HID->prev != NULL){
	pn_HID = pn_HID->prev;
	free(pn_HID->next);
	}
	free(pn_HID);
	
	return 0;
}

