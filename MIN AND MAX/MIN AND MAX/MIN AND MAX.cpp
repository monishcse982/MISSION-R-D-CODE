// MIN AND MAX.cpp : Defines the entry point for the console application.
//1. Given an integer array and length as inputs, write a function to find the max value and min value of the array. example: input array 2, 4, -6, 8, -2 and 5 as inputs, output is: max: 8, min: -6
//

#include "stdafx.h"
int* min_and_max(int input_array[],int length)
{
	int loop1, min_max[2] = {input_array[0], input_array[0]};
	for(loop1=1;loop1<length;loop1++)
	{
		if(min_max[0]>input_array[loop1])
		{
			min_max[0] = input_array[loop1];
		}

		if(min_max[1]<input_array[loop1])
		{
			min_max[1] = input_array[loop1];
		}
	}
	return(min_max);
}

void test_min_and_max()
{
	int input_array[2][10] = {{2, 4, -6, 8, -2, 5, 45, 673, -4934, 9458},{-34, 34, 78, 2, 9, 56, 99, 24, 76, 16}},i;
	int output_results[2][2] = {{9458,-4934},{99,-34}};
	int *return_ptr;
	for(i=0;i<2;i++)
	{
		return_ptr = min_and_max(input_array[i],10);
		if(*return_ptr++ == output_results[i][1])
		{
			if(*return_ptr == output_results[i][0])
			printf("ACCEPTED\n");
		}
		else{printf("REJECTED\n");}
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	test_min_and_max();
	getchar();
	return 0;
}

