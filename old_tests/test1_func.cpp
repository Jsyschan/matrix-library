#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include "matrix.h"
using namespace std;

int main(int argc, char *argv[]){
	srand(time(NULL));

	Matrix test(4,7);
	test.fake();
	printf("Printing test array:\n");
	test.print();

	Matrix copy(test);
	printf("Printing copy array:\n");
	copy.print();

	printf("\n\nMultiplying test array by 10:\t\tThis is Test 1\n\n");
	//Matrix test1 = test.mult(10.0);
	//Matrix test1 = test.mult((double) 10);
	Matrix test1 = test.mult(20);
	test1.print();


	printf("\n\nAdding test array and copy array:\t\tThis is Test 2\n\n");
	Matrix test2 = test.add(copy); 
	test2.print();

	printf("\n\nSubtracting Array 1 and Array 2:\t\tThis is Test 3\n\n");
	Matrix test3 = test1.sub(test2);
	test3.print();

	printf("\n\nTesting the Hadamard Product, with 2 and 3:\t\tThis is test 4\n\n");
	Matrix test4 = test2.hadamard(test3);
	test4.print();


	return 0;
}


