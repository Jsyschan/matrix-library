#include <assert.h>
#include <cstdlib>

#include "matrix.h"
#include "nn1.h"

using namespace std;

//Constructors and Destructors
Network::Network(){		this->hidden = NULL; 	this->weights = NULL; 	this->bias = NULL;	}
Network::~Network(){ 	free(hidden);			free(weights);			free(bias);			}


//Dummy Func
double random(double x){ return x+1; }
double sigmoid(double X){   return X+1 ;                  }
double dsigmoid(double X){  return X+1;   }


//double random(double x){ return (double)(((rand() %10000)+1)/10000)+0.5; }
//double sigmoid(double X){   return 1/(1+exp(-X));                   }
//double dsigmoid(double X){  return exp(-X) / (pow(1+exp(-X), 2));   }



//Initialize Neural Network
void Network::initialize(int numInputN, int numOutputN, int numHiddenN, int numHiddenL, double LR){
	assert(numInputN > 0 && numOutputN > 0 && numHiddenN > 0 && numHiddenL > 0 && LR > 0);

	//Initialize the Network Base Parameters
	this->nIN = numInputN;
	this->nON = numOutputN;
	this->nHN = numHiddenN;
	this->nHL = numHiddenL;
	this->learn_rate = LR;

	//For now, make all hidden layers have the same # of neurons
	//Initialize the matrices: the rows represent each 'layer' in the network
	this->hidden = (Matrix *) malloc(sizeof(Matrix)*nHL); //Hidden Matrix 

	for(int i=0; i < nHL; i++)		this->hidden[i] = Matrix(1,nHN);

	this->weights = (Matrix *) malloc(sizeof(Matrix)*(nHL +1)); //Matrices of Weights
	for(int i=0; i < (nHL + 1); i++){
		if(i==0)				this->weights[i] = Matrix(this->nIN,this->nHN);
		else if(i == nHL)		this->weights[i] = Matrix(this->nHN,this->nON);
		else					this->weights[i] = Matrix(this->nHN,this->nHN);				
	}

	this->bias = (Matrix *) malloc(sizeof(Matrix)*(nHL +1)); //Matrices of Biases
	for(int i=0; i < (nHL + 1); i++){
		if(i == nHL)			this->bias[i] = Matrix(1,this->nON);
		else					this->bias[i] = Matrix(1,this->nHN);				
	}
}

void Network::randomize(){
	for(int i=0; i<((this->nHL)+1); i++)		this->bias[i] = this->bias[i].applyFunc(random);
	for(int i=0; i<((this->nHL)+1); i++)		this->weights[i] = this->weights[i].applyFunc(random);	
}


//Matrix Network::iterate(Matrix &input){
//Matrix Network::iterate(const Matrix &input){
Matrix Network::iterate(const Matrix &input){
	
	Matrix output;
	for(int i=0; i<=(this->nHL); i++){ //'i' represents the layer that you are trying to calculate
		//printf("----------------------------------------------------------------------\n");
		//printf("Value of I is %d\n\n",i);
		if(i == 0)	//First Hidden Layer	
		{
			//printf("Input: \n"); input.print();
			//printf("Weight:\n"); this->weights[0].print();
			//printf("Biased:\n"); this->bias[0].print();
			this->hidden[0] = (input*this->weights[0])+this->bias[0];
			this->hidden[0] = this->hidden[0].applyFunc(sigmoid);
			//printf("Result:\n"); this->hidden[0].print();
		} 
		else if(i == (this->nHL))	//At the last hidden layer
		{
			//printf("Input: \n"); input.print();
			//printf("Weight:\n"); this->weights[this->nHL].print();
			//printf("Biased:\n"); this->bias[0].print();
			output = (this->hidden[(this->nHL)-1]*this->weights[this->nHL])+this->bias[this->nHL];
			output = output.applyFunc(sigmoid);		} 
		else
		{
			//printf("Input Hidden %d: \n",i-1); this->hidden[i-1].print();
			//printf("Weight %d:\n",i); this->weights[i].print();
			printf("Biased %d:\n",i); this->bias[i].print();
			this->hidden[i] = ((this->hidden[i-1])*(this->weights[i]))+(this->bias[i]);
			this->hidden[i] = this->hidden[i].applyFunc(sigmoid);
		} 

	}	
	/*
	   hidden[0] = (input*weights[0])+bias[0];		hidden[0] = hidden[0].applyFunc(sigmoid);
	   hidden[1] = (hidden[0]*weights[1])+bias[1];	hidden[1] = hidden[1].applyFunc(sigmoid);
	   hidden[2] = (hidden[1]*weights[2])+bias[2]); hidden[2] = hidden[2].applyFunc(sigmoid);
	   output = (hidden[2]*weights[3])+bias[3];	   output = output.applyFunc(sigmoid);
	 */
	return output;
}
























//
void Network::print(){
	printf("------------------------------------------------------\n\n");
	printf("Hidden Layers:\n");
	for(int i=0; i<nHL; i++){
		printf("\nLayer %d:\t",i);
		hidden[i].print();
	}

	printf("------------------------------------------------------\n\n");
	printf("Weights:\n");
	for(int i=0; i<(nHL+1); i++){
		printf("\nLayer %d:\t",i);
		weights[i].print();
	}


	printf("------------------------------------------------------\n\n");
	printf("Biases:\n");
	for(int i=0; i<(nHL+1); i++){
		printf("\nLayer %d:\t",i);
		bias[i].print();
	}



}


















