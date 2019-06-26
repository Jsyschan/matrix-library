#include <assert.h>
#include <cstdlib>

#include "matrix.h"
#include "nn1.h"

using namespace std;

//Constructors and Destructors
Network::Network(){		
	this->hidden = NULL; 	
	this->weights = NULL; 	
	this->bias = NULL;	
}

Network::~Network(){ 	
	free(weights);
	free(bias);
	free(dweights);
	free(dbias);
	free(hidden);
}


//Dummy Func
//double random(double x){ return (double) ( (rand()*10000) % 5); }
//double sigmoid(double X){   return X+1.0; }
//double dsigmoid(double X){  return X/10.0;   }

double random(double x){ return (double) ((rand() %10000)+1)/10000-0.5; }
double sigmoid(double X){   return 1/(1+exp(-X));                   }
double dsigmoid(double X){  return exp(-X) / (pow(1+exp(-X), 2));   }



//Initialize Neural Network
void Network::initialize(int n_IN, int n_OUT, int l_HID, struct hlist *n_HID, double LR){

	assert(n_IN > 0 && n_OUT > 0 && n_HID != NULL && l_HID > 0 && LR > 0.0);

	//Check here and make sure that the # of hidd. neurons/layer match up with # of hidden layers
	int cl_HID = 0;	struct hlist *pn_HID = n_HID;
	while(pn_HID != NULL){		cl_HID++;		pn_HID = pn_HID->next;	}
	if(cl_HID != l_HID){
		printf("ERROR: Mismatch between # of hidd. neurons/layer & number of hidd. layers!\n");
		printf("Number of Hidden Layers: %-3d\tNumber of hidd. neurons/layer: %-3d\n",l_HID,cl_HID);
		exit(-1);
	}

	//Initialize the Network Base Parameters
	this->nIN = n_IN;
	this->nON = n_OUT;
	this->nHL = l_HID;
	this->learn_rate = LR;

	//Initialize the matrices: the rows represent each 'layer' in the network, from 0 to nHL-1

	//Hidden Matrices
	pn_HID = n_HID;
	this->hidden = (Matrix *) malloc(sizeof(Matrix)*nHL); 
	for(int i=0; i < nHL; i++){
		this->hidden[i] = Matrix(1,pn_HID->H);
		pn_HID = pn_HID->next;
	}


	//Weight Matrices
	pn_HID = n_HID;
	this->weights = (Matrix *) malloc(sizeof(Matrix)*(nHL +1));
	this->dweights = (Matrix*) malloc(sizeof(Matrix)*(nHL +1));

	for(int i=0; i <= nHL; i++){
		if(i==0){		 
			this->weights[i] = Matrix(this->nIN,pn_HID->H); //First H. Layer, from Input to H0
			this->dweights[i] = Matrix(this->nIN,pn_HID->H); //First H. Layer, from Input to H0
		}
		else if(i == nHL){
			this->weights[i] = Matrix(pn_HID->H,this->nON); //Last H. Layer, from H[nHL-1] to Output
			this->dweights[i] = Matrix(pn_HID->H,this->nON); //Last H. Layer, from H[nHL-1] to Output
		}
		else{
			this->weights[i] = Matrix(pn_HID->H,pn_HID->next->H);	//All Layers in between
			this->dweights[i] = Matrix(pn_HID->H,pn_HID->next->H);	//All Layers in between
			pn_HID = pn_HID->next;
		}
	}	

	//Bias Matrices
	pn_HID = n_HID;
	this->bias = (Matrix *) malloc(sizeof(Matrix)*(nHL +1));
	this->dbias = (Matrix*) malloc(sizeof(Matrix)*(nHL +1));

	for(int i=0; i <= nHL ; i++){
		if(i == nHL)			{
			this->bias[i] = Matrix(1,this->nON);
			this->dbias[i] = Matrix(1,this->nON);
		}
		else{
			this->bias[i] = Matrix(1,pn_HID->H);				
			this->dbias[i] = Matrix(1,pn_HID->H);				
			pn_HID = pn_HID->next;
		}
	}

	//Hidden Matrices
	//for(int i=0; i < nHL; i++)		this->hidden[i].fake1();
	//Weight Matrices
	//for(int i=0; i < (nHL + 1); i++) this->weights[i].fake1();
	//Bias Matrices
	//for(int i=0; i < (nHL + 1); i++) this->bias[i].fake1();

}

//Use this to randomize the weights and biases
void Network::randomize(){
	for(int i=0; i<((this->nHL)+1); i++)		this->bias[i] = this->bias[i].applyFunc(random);
	for(int i=0; i<((this->nHL)+1); i++)		this->weights[i] = this->weights[i].applyFunc(random);	
}


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
			this->hidden[0] = (input->*this->weights[0])+this->bias[0];
			this->hidden[0] = this->hidden[0].applyFunc(sigmoid);
			//printf("Result:\n"); this->hidden[0].print();
		} 
		else if(i == (this->nHL))	//At the last hidden layer
		{
			//printf("Input: \n"); input.print();
			//printf("Weight:\n"); this->weights[this->nHL].print();
			//printf("Biased:\n"); this->bias[0].print();
			output = (this->hidden[(this->nHL)-1]->*this->weights[this->nHL])+this->bias[this->nHL];
			output = output.applyFunc(sigmoid);		} 
		else
		{
			//printf("Input Hidden %d: \n",i-1); this->hidden[i-1].print();
			//printf("Weight %d:\n",i); this->weights[i].print();
			//printf("Biased %d:\n",i); this->bias[i].print();
			this->hidden[i] = ((this->hidden[i-1])->*(this->weights[i]))+(this->bias[i]);
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



//Back Propagation Function
void Network::back_prop(const Matrix &input, const Matrix &output, const Matrix &ideal){

	Matrix diff = output - ideal;
	Matrix temp;
	for(int i=this->nHL; i>=0; i--){
		
		
		if( i == this->nHL){
			temp = (this->hidden[i-1]->*this->weights[i])+this->bias[i];
			temp = temp.applyFunc(dsigmoid);
			this->dbias[i] = diff*temp;
			this->dweights[i] = this->hidden[i-1].transpose() ->* this->dbias[i];
		}
		else if( i == 0){
			temp = (input->*this->weights[i])+this->bias[i];
			temp = temp.applyFunc(dsigmoid);

			this->dbias[i] = this->dbias[i+1] ->* this->weights[i+1].transpose();
			this->dbias[i] = this->dbias[i]*temp;



			this->dweights[i] = input.transpose() ->* this->dbias[i];
		}
		else{


			temp = (this->hidden[i-1]->*this->weights[i])+this->bias[i];
			temp = temp.applyFunc(dsigmoid);


			this->dbias[i] = this->dbias[i+1] ->* this->weights[i+1].transpose();
			this->dbias[i] = this->dbias[i]*temp;

			this->dweights[i] = this->hidden[i-1].transpose() ->* this->dbias[i];

		}
	}
/*
	printf("-------------------------------------------------------\n\n");
	printf("Output Diff:\n");
	diff.print();

	printf("------------------------------------------------------\n\n");
	printf("derivative Weights:\n");
	for(int i=0; i<(nHL+1); i++){
		printf("\nLayer %d:\t",i);
		dweights[i].print();
	}


	printf("------------------------------------------------------\n\n");
	printf("derivative Biases:\n");
	for(int i=0; i<(nHL+1); i++){
		printf("\nLayer %d:\t",i);
		dbias[i].print();
	}
*/

	//UPDATING
	for(int i=0; i<=(this->nHL); i++){
		this->weights[i] = (this->weights[i]) - (this->dweights[i] * learn_rate);
		this->bias[i] = (this->bias[i]) - (this->dbias[i] * learn_rate);


	}




	//printf("Leaving dNN PRINT\n");











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
		printf("\nLayer %d:\n",i);
		weights[i].print();
	}


	printf("------------------------------------------------------\n\n");
	printf("Biases:\n");
	for(int i=0; i<(nHL+1); i++){
		printf("\nLayer %d:\n",i);
		bias[i].print();
	}

	printf("Leaving NN PRINT\n");

}


















