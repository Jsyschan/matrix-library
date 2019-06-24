#ifndef __NN1_H__
#define __NN1_H__

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <cmath>

#include "matrix.h"
using namespace std;

struct hlist{
	int H;
	hlist *next;
	hlist *prev;
};


class Network{
	public:
		Network();
		~Network();
		void initialize(int,int,int,struct hlist *,double);	//Initialize the Network
		void print();
		void randomize();
		Matrix iterate(const Matrix &); //Need to pass by reference else deletes it?
		void back_prop(const Matrix &, const Matrix &, const Matrix &); 
		//void print_output(){ output.print(); }

	private:
		//Base Parameters
		double learn_rate;	//Learning Rate of Network
		int nIN;		//Number of Input Neurons
		int nON;		//Number of Output Neurons
		//int nHN;		//Number of Hidden Neurons
		int nHL;		//Number of Hidden Layers

		//Inner Workings: Array of Matrices of different sizes
		Matrix *hidden;		//Matrix for Hidden Layer
		Matrix *weights;	//Matrix for Weights
		Matrix *bias;		//Matrix for Bias
		Matrix *dweights;	//Matrix for rate of change for weights
		Matrix *dbias;		//Matirx for rate of change for biases

		//Matrix output;

};

//Global functions
double random(double);
double sigmoid(double);
double dsigmoid(double);


#endif
