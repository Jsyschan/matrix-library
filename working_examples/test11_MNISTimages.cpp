#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

#include "matrix.h"
#include "nn1.h"

#define TRAIN_SET "data/train-images-idx3-ubyte"
#define TEST_SET "data/t10k-images-idx3-ubyte"

using namespace std;


struct idx{
	int magic;
	int num_img;
	int nrows;
	int ncols;
	Matrix *data;
};

int read_Training(struct idx *, char *);

int main(int argc, char *argv[]){ 
	srand(time(NULL));

	//Initialization
	double learn = 0.5;	int n_IN = 2;	int n_OUT = 2;	
	int l_HID = 4; int nInt = 10000; int error;
	int counter = 0;
	unsigned long tmplong = 0;
	unsigned char tmpchar;
	bool first = true;

	struct idx TRAIN;

	FILE *fptr;
	fptr = fopen(TRAIN_SET,"rb");
	if(fptr == NULL)		
		printf("ERROR: Unable to open %s\n",TRAIN_SET);
	else{

		while(!feof(fptr)){

			switch(counter){
				case 0:
					tmplong = 0;	
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					printf("1. The Magic number is 0x%-8x, or %d\n",tmplong,tmplong); TRAIN.magic = tmplong;
					counter++;
					break;
				case 1:
					tmplong = 0;	
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					printf("2. Number of Images is 0x%-8x, or %d\n",tmplong,tmplong); TRAIN.num_img = tmplong;
					counter++;
					break;
				case 2:
					tmplong = 0;	
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					printf("3.   Number of Rows is  0x%-8x, or %d\n",tmplong,tmplong); TRAIN.nrows = tmplong;
					counter++;
					break;
				case 3:
					tmplong = 0;	
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					printf("4.   Number of Cols is 0x%-8x, or %d\n",tmplong,tmplong); TRAIN.ncols = tmplong;
					counter++;
					break;
				default:
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					//printf("\ntmpchar is %3c, as a number, it's  0x%20x\n",tmpchar,tmpchar);
					break;
			}
		}
		printf("\nEND OF LINE MAN\n");
	}
	fclose(fptr);

	printf("\nFrom the structure:\n");
	printf("\tMagic = %d\n",TRAIN.magic);
	printf("\tNimgs = %d\n",TRAIN.num_img);
	printf("\tNrows = %d\n",TRAIN.nrows);
	printf("\tNcols = %d\n",TRAIN.ncols);




	/*
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

	 */
	return 0;
}


















int read_Training(struct idx * set, char* training_file){


	unsigned long tmplong = 0;
	unsigned char tmpchar;
	FILE *fptr;
	struct idx* tmpset = set;
	if(set 


	fptr = fopen(training_file,"rb");
	if(fptr == NULL)		
		printf("ERROR: Unable to open %s\n",training_file);
	else{

		while(!feof(fptr)){

			switch(counter){
				case 0:
					tmplong = 0;	
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					printf("1. The Magic number is 0x%-8x, or %d\n",tmplong,tmplong); TRAIN.magic = tmplong;
					counter++;
					break;
				case 1:
					tmplong = 0;	
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					printf("2. Number of Images is 0x%-8x, or %d\n",tmplong,tmplong); TRAIN.num_img = tmplong;
					counter++;
					break;
				case 2:
					tmplong = 0;	
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					printf("3.   Number of Rows is  0x%-8x, or %d\n",tmplong,tmplong); TRAIN.nrows = tmplong;
					counter++;
					break;
				case 3:
					tmplong = 0;	
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					tmplong = tmplong << 8;
					tmplong = tmplong | tmpchar;
					printf("4.   Number of Cols is 0x%-8x, or %d\n",tmplong,tmplong); TRAIN.ncols = tmplong;
					counter++;
					break;
				default:
					error = fscanf(fptr,"%c",&tmpchar);	if(error == 0) printf("ERROR: Didn't read anything\n");
					//printf("\ntmpchar is %3c, as a number, it's  0x%20x\n",tmpchar,tmpchar);
					break;
			}
		}
		printf("\nEND OF LINE MAN\n");
	}
	fclose(fptr);



}
