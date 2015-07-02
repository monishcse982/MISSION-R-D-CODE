// S1Q5.cpp : Given an unsigned array which has values from 1 to 1000 and length as inputs, write a function to get the Nth (n also as input) top element of the array. example: array input: 21, 3, 44, 6, 13, 5, 51, 23, 1, 18 and N as 3 output is 23.
//

#include "stdafx.h"

int split_array(int* input_array, int start, int end)
{
	int high, low, pivot  = input_array[start];
	low = start;
	high = end;
	while(low<high)
	{
		while(input_array[low] <=pivot)
		{
			low++;
		}
		while(input_array[high] > pivot)
		{
			high--;
		}
		if(low<high)
		{
			input_array[low] = input_array[low] + input_array[high];
			input_array[high] = input_array[low] - input_array[high];
			input_array[low] = input_array[low] - input_array[high];
		}
	}
	input_array[start] = input_array[high];
	input_array[high] = pivot;
	return high;
}

void Quick_Sort(int* input_array, int start, int end)
{
	int pivot;
	if(end>start)
	{
		pivot = split_array(input_array, start, end);
		Quick_Sort(input_array,start,pivot-1);
		Quick_Sort(input_array,pivot+1,end);

	}
}

void print_array(int* input_array, int len)
{
	for(int i=0;i<len;i++)
	{
		printf("%d ",input_array[i]);
	}
}

int N_max(int* input_array, int length, int position)
{
	int loop1;
	Quick_Sort(input_array,0,length-1);
	print_array(input_array, length);
	return (input_array[length - (position)]);
}

void test_N_max()
{
	int input_array[4][10] = {
								{21, 3, 44, 6, 13, 5, 51, 23, 1, 18},
								{34,98,28,57,20,84,48,36,94,123},
								{3,2,1},
								{96,45}
							 };
	int length_of_inputs[4] ={10,10,3,2}; 
	int N_value[4] = {3,5,3,2};
	int output_array[4] = {23,57,1,45};
	int result = 1, return_ptr;
	int loop1;
	for(loop1=0;loop1<4;loop1++)
	{
		int val = N_max(input_array[loop1],length_of_inputs[loop1],N_value[loop1]);
		if( output_array[loop1] == val)
		{
			printf("\nACCEPTED\n");
		}
		else{
			printf("\nREJECTED\n");}

	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_N_max();
	getchar();
	return 0;
}