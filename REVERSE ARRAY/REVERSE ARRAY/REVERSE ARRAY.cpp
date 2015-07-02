// REVERSE ARRAY.cpp : Given an integer array and its lengths as inputs, write a function to reverse the array

#include "stdafx.h"
void reverse_array(int* input_array, int length)
{
	int loop1,loop2;
	for(loop1=0,loop2=length-1;loop1<loop2;loop1++,loop2--)
	{
		input_array[loop1] = input_array[loop1] + input_array[loop2];
		input_array[loop2] =  input_array[loop1] - input_array[loop2];
		input_array[loop1] =  input_array[loop1] - input_array[loop2];
	}
}

void test_reverse_array()
{
	int input_array[5][10] = {
								{1,2,3,4,5,6,7,8,9,10},
								{10,9,8,7,6,5,4,3,2,1},
								{23,535,57,23,656,32,65,57,23},
								{5},{1,2}
							 };
	int output_array[5][10] = {
								{10,9,8,7,6,5,4,3,2,1},
								{1,2,3,4,5,6,7,8,9,10},
								{23,57,65,32,656,23,57,535,23},
								{5},{2,1}
							  };
	int size_of_inputs[5] ={10,10,9,1,2};
	int loop1,loop2,result=1,no_of_inputs=5;

	for(loop1=0;loop1<no_of_inputs;loop1++)
	{
		reverse_array(input_array[loop1], size_of_inputs[loop1]);

		for(loop2=0;loop2<size_of_inputs[loop1];loop2++)
		{
			if(input_array[loop1][loop2] == output_array[loop1][loop2])
			{
				continue;
			}
			else{result = 0; break;}
		}
		if(result == 0)
		{
			printf("REJECTED\n");
			result = 1;
		}
		else{printf("ACCEPTED\n");}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	test_reverse_array();
	getchar();
	return 0;
}

