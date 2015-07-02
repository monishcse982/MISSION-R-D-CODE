// S1Q2.c.cpp : Defines the entry point for the console application.
//Given an integer array and length as inputs, write a function to remove adjacent duplicate values of the array(same array as return, dont use extra array).
//examples:input array 1,2,2,5,2,6,6,6,3,2,6,9 output is: 1,2,5,2,6,3,2,6,9

#include "stdafx.h"

void remove_adjacent_duplicates(int * input_array, int length)
{
    int loop1=0;
	while(input_array[loop1]!='\0')
	{
		if(input_array[loop1] != input_array[loop1+1])
			{
				loop1++;
				continue;
			}
		if(input_array[loop1] == input_array[loop1+1])
		{
			int loop2 = loop1+1;
			while(input_array[loop2+1]!='\0')
			{
				input_array[loop2] = input_array[loop2+1] + input_array[loop2];
				input_array[loop2+1] = input_array[loop2] - input_array[loop2+1];
				input_array[loop2] = input_array[loop2] - input_array[loop2+1];
				loop2++;
			}
			input_array[loop2] = '\0';
		}
	}
}

void test_remove_adjacent_duplicates()
{
	int input_array[2][20] = {
								{1,2,2,5,2,6,6,6,3,2,6,9},
								{1,2,1}
							 };
	int output_results[2][20] = {
								{1,2,5,2,6,3,2,6,9},
								{1,2,1}
						 };
	int size_of_inputs[2] = {12,3};
	int size_of_outputs[2] = {9,3};
	int loop1, loop2,*return_ptr;
	int result=0;
	for(loop1=0;loop1<2;loop1++)
	{
		remove_adjacent_duplicates(input_array[loop1],size_of_inputs[loop1]);
		
		for(loop2=0;loop2<size_of_outputs[loop1];loop2++)
		{
			if(input_array[loop1][loop2] == output_results[loop1][loop2])
			{
				continue;
			}
			else{result = -1; break;}
		}

		if(result == 0)
		{
			printf("ACCEPTED\n");
		}
		else
		{
			printf("REJECTED\n");
			result = 0;
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	test_remove_adjacent_duplicates();
	getchar();
	return 0;
	
}

