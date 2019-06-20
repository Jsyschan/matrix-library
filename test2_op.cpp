#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include "matrix.h"
using namespace std;

double SP(double X){
	return (X+1);
}


int main(int argc, char *argv[]){
	srand(time(NULL));

	Matrix test(3,3);
	test.fake();
	printf("Printing test array:\n");
	test.print();

	Matrix copy;
	copy = test;
	printf("Printing copy array:\n");
	copy.print();

	printf("multiplying 2 to copy: TEST 2\n\n");
	Matrix test2 = copy*3;
	test2.print();

	printf("Adding copy and copy together:\t\tTEST 3\n\n");
	Matrix test3 = copy + test;
	test3.print();

	printf("\n\nSubtracting Copy from Test to get 0s\t\tTEST 4\n\n");
	Matrix test4 = copy - test;
	test4.print();


	printf("\n\nTesting Dot Product:\t\t\tTEST 5\n\n");
	Matrix left(3,2); left.fake();
	printf("\nLEFT: \n\n");
	left.print();
	Matrix rite(2,1); rite.fake();
	printf("\nRIGHT:\n\n");
	rite.print();
	Matrix test5 = left * rite;
	printf("\nRESULT:\n\n");
	test5.print();


	printf("\n\nTransposing test5:\t\tTEST 6\n\n");
	Matrix test6 = test5.transpose();
	test6.print();

	printf("\n\nTesting Hadamard Function with test6\t\tTEST 7\n\n");
	Matrix test7 = test6.hadamard(test6);
	test7.print();




	printf("\n\nTesting function parameter, func SP which returns X+1\t\tTEST8\n\n");
	printf("X is %f\t\tWorking on test7\n\n",9.0);
	printf("applyFunc takes the function, and uses it on every member in the matrix\n");
	printf("So, if each element can be thought of as X, it just increases the elements in test7 by 1\n\n");
	Matrix test8 = test7.applyFunc(SP);
	test8.print();


	printf("\n\nNow, let's try with multiple matrices and functions to put it all together\n\n");
	Matrix A(2,3); A.fake();
	Matrix B(2,3); B.fake(2);
	Matrix C(3,1); C.fake(3);

	printf("\nMatrix A:\n\n");	A.print();
	printf("\nMatrix B:\n\n");	B.print();
	printf("\nMatrix C:\n\n");	C.print();

	//Matrix R1 = A*7 + B * C;
	//Matrix R2 = (A*7) + B * C;
	Matrix R3 = ((A*2)+B)*C;
	Matrix R4 = ((A*2)+B)* C.applyFunc(SP);
	//printf("\nMatrix R1:\n\n");	R1.print();
	//printf("\nMatrix R2:\n\n");	R2.print();
	printf("\nMatrix R3:\n\n");	R3.print();
	printf("\nMatrix R4:\n\n");	R4.print();
	




	return 0;
}

