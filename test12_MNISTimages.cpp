#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>
#include <cstring>

#include "matrix.h"
#include "nn1.h"

#define TRAIN_SET "data/train-images-idx3-ubyte"
#define TEST_SET "data/t10k-images-idx3-ubyte"

using namespace std;


struct idx{
	idx();
	~idx();
	int magic;
	int num_img;
	int nrows;
	int ncols;
	Matrix *data;
};

idx::idx(){}
idx::~idx(){

}

struct idx* read_Training(struct idx *, const char *);

int main(int argc, char *argv[]){ 
	srand(time(NULL));

	//Initialization
	double learn = 0.5;	int n_IN = 2;	int n_OUT = 2;	
	int l_HID = 4; int nInt = 10000; int error;

	struct idx* TRAIN = NULL;
	struct idx* TEST = NULL;

	TRAIN = read_Training(TRAIN,TRAIN_SET);
	TEST = read_Training(TEST,TEST_SET);



	printf("\tMagic = %d\n",TRAIN->magic);
	printf("\tNimgs = %d\n",TRAIN->num_img);
	printf("\tNrows = %d\n",TRAIN->nrows);
	printf("\tNcols = %d\n",TRAIN->ncols);



	printf("\tMagic = %d\n",TEST->magic);
	printf("\tNimgs = %d\n",TEST->num_img);
	printf("\tNrows = %d\n",TEST->nrows);
	printf("\tNcols = %d\n",TEST->ncols);


	//for(int i=0; i<(TEST->num_img); i++)
	//	printf("\tTEST SAMPLE %7d is size %3d x %-3d\n",i,TEST->data[i].getRows(),TEST->data[i].getCols());

	printf("Testing:\n\n");
	TEST->data[12].print();

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
}//ENDL


















struct idx* read_Training(struct idx *set, const char* filename){
	if(strncmp(filename,TRAIN_SET,90) == 0) printf("Reading in Training Set\n");
	if(strncmp(filename,TEST_SET,90) == 0) printf("Reading in Testing Set\n");

	unsigned long tmplong = 0;
	unsigned char tmpchar;
	int counter = 0, error,i,j,n;
	FILE *fptr;

	if(set == NULL) 	set = (struct idx *) malloc(sizeof(struct idx));

	fptr = fopen(filename,"rb");
	if(fptr == NULL){		
		printf("ERROR: Unable to open %s\n",filename);
		return NULL;
	}
	else{
		while(!feof(fptr)){
			switch(counter){
				case 0:
					tmplong = 0;	
					for(i=0; i<4; i++){
						error = fscanf(fptr,"%c",&tmpchar);	
						if(error == 0) printf("ERROR: Didn't read anything\n");
						tmplong = tmplong << 8;
						tmplong = tmplong | tmpchar;
					}
					set->magic = tmplong;
					counter++;
					break;
				case 1:
					tmplong = 0;	
					for(i=0; i<4; i++){
						error = fscanf(fptr,"%c",&tmpchar);	
						if(error == 0) printf("ERROR: Didn't read anything\n");
						tmplong = tmplong << 8;
						tmplong = tmplong | tmpchar;
					}
					set->num_img = tmplong;
					counter++;
					break;
				case 2:
					tmplong = 0;	
					for(i=0; i<4; i++){
						error = fscanf(fptr,"%c",&tmpchar);	
						if(error == 0) printf("ERROR: Didn't read anything\n");
						tmplong = tmplong << 8;
						tmplong = tmplong | tmpchar;
					}
					set->nrows = tmplong;
					counter++;
					break;
				case 3:
					tmplong = 0;	
					for(i=0; i<4; i++){
						error = fscanf(fptr,"%c",&tmpchar);	
						if(error == 0) printf("ERROR: Didn't read anything\n");
						tmplong = tmplong << 8;
						tmplong = tmplong | tmpchar;
					}
					set->ncols = tmplong;
					set->data = (Matrix *) malloc(sizeof(Matrix)*(set->num_img));
					for(n=0; n<(set->num_img); n++)
						set->data[n] = Matrix(set->nrows,set->ncols);					
					counter++;
					break;
				case 4:
					for(n=0; n<(set->num_img); n++){
						for(i=0; i<(set->nrows); i++){
							for(j=0; j<(set->ncols); j++){
								error = fscanf(fptr,"%c",&tmpchar);	
								if(error == 0) printf("ERROR: Didn't read anything\n");
								set->data[n](i,j) = (double) tmpchar;
							}
						}
					}
					//.printf("\ttmpchar as a number, it's %-5d, or  0x%8x\n",tmpchar,tmpchar);
					//i,TEST->data[i].getRows(),TEST->data[i].getCols());

					break;
				default:
					printf("ERROR: Something has gone wrong\n");
					fclose(fptr);
					return NULL;
			}
		}
	}
	fclose(fptr);
	return set;
}
