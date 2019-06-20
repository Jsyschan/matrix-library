#ifndef __NN1_H__
#define __NN1_H__

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

#include "matrix.h"
using namespace std;

class Network{
	public:
		Network();
		~Network();
		void initialize(int,int,int,int,double);	//Initialize the Network
		void print();
		void randomize();
		//Matrix iterate(Matrix &); //Need to pass by reference else deletes it?
		Matrix iterate(const Matrix &); //Need to pass by reference else deletes it?
		//Matrix iterate(const Matrix &); //Need to pass by reference else deletes it?

		//double random(double x){ return (double)(((rand() %10000)+1)/10000)+0.5; }
		//double sigmoid(double X){	return 1/(1+exp(-X));					}
		//double dsigmoid(double X){	return exp(-X) / (pow(1+exp(-X), 2));	}
	private:
		//Base Parameters
		double learn_rate;	//Learning Rate of Network
		int nIN;		//Number of Input Neurons
		int nON;		//Number of Output Neurons
		int nHN;		//Number of Hidden Neurons
		int nHL;		//Number of Hidden Layers

		//Inner Workings
		Matrix *hidden;		//Matrix for Hidden Layer, each row represents one hidden layer
		Matrix *weights;		//Matrix for Weights
		Matrix *bias;		//Matrix for Bias

};

//Global functions
double random(double);
double sigmoid(double);
double dsigmoid(double);
//double random(double x){ return (double)(((rand() %10000)+1)/10000)+0.5; }
//double sigmoid(double X){	return 1/(1+exp(-X));					}
//double dsigmoid(double X){	return exp(-X) / (pow(1+exp(-X), 2));	}


#endif
