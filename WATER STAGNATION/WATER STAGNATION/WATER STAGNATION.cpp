// WATER STAGNATION.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

int minimum_of_values(int value_1,int value_2)
{
	if (value_1 > value_2)
	{ 
		return value_2; 
	}
	return value_2;
}

void max_stagnant_water_volume(int input_array[],int len,int output_array[])
{
	int iter_loop1=0,iter_loop2=0;
	output_array[0] = 0;
	for (int iter_loop2 = 1; iter_loop2 < len; iter_loop2++)
	{
		if (input_array[iter_loop2] > input_array[iter_loop2 - 1])
		{
			int k =iter_loop2+1;
			while (k<iter_loop2)
			{
				int current_max_value;
				if (input_array[iter_loop2] < input_array[iter_loop2])
				{
					current_max_value = input_array[iter_loop2];
				}
				else
				{
					current_max_value = input_array[iter_loop2];
				}
				if (input_array[iter_loop2] > input_array[k])
				{
					output_array[k] = current_max_value - input_array[k];
				}
				k++;
			}
			output_array[iter_loop2] = 0;
		}
		else if (input_array[iter_loop2 - 1] <= input_array[iter_loop2])
		{
			output_array[iter_loop2] = 0;
		}
		else if (input_array[iter_loop2 - 1]>input_array[iter_loop2] && input_array[iter_loop2 + 1] > input_array[iter_loop2])
		{
			output_array[iter_loop2] = minimum_of_values((input_array[iter_loop2 - 1] - input_array[iter_loop2]), (input_array[iter_loop2 + 1]- input_array[iter_loop2]));
		}
		else if (input_array[iter_loop2]<input_array[iter_loop2-1])
		{
			output_array[iter_loop2] = -1;
		}
		if (input_array[iter_loop2]>input_array[iter_loop2])
		{
			iter_loop2 = iter_loop2;
		}
	}
	int s, e,sum,max_sum=0,index_1=-1,index_2=-1;
	for (int iter_loop3 = 0; iter_loop3< len; iter_loop3++)
	{
		sum = 0;
		if (output_array[iter_loop3] != 0)
		{
			s =e= iter_loop3;
			if (s!=0)
			{
				s = iter_loop3 - 1;
			}
			while (e<len && output_array[e] != 0)
			{
				sum += output_array[e];
				e++;
				iter_loop3 = e-1;
			}
			if (sum > max_sum)
			{
				index_1 = s;
				index_2 = e;
				max_sum = sum;
			}
		}
	}
	int output_index = 0;
	for (int iter_loop3 = index_1; iter_loop3 <= index_2; iter_loop3++)
	{
		if (index_1 == -1 && index_2 == -1)
		{
			break;
		}
		output_array[output_index++] = input_array[iter_loop3];
	}
}

int compare(int input_array1[], int input_array2[],int length)
{
	for (int iter_loop = 0; iter_loop < length; iter_loop++)
	{
		if (input_array1[iter_loop] != input_array2[iter_loop])
			return 0;
	}
	return 1;
}

void testcases()
{
	int i = 0;
	int input_array[6][10]= {
		{ 4, 4, 4, 4, 4 }, 
		{ 1,3,5,7},
		{1,0,3,0,5,0,7},
		{7, 0, 5, 0, 3, 0, 1}
	};

	int input_length[6] = {5,4,7,7};

	int output_array[6][10] = {
		{'\0'},
		{'\0'},
		{5,0,7},
		{7,0,5}
	};

	int output_length[6] = {0,0,3,3};

	for (int iter_loop = 0; iter_loop<5; iter_loop++)
	{
		int *result_array = (int*)malloc(20*sizeof(int));
		max_stagnant_water_volume(input_array[iter_loop],input_length[iter_loop],result_array);
		if (compare(output_array[iter_loop],result_array,output_length[iter_loop]) == 1)
		{
			printf("PASSED\n");
		}
		else
		{
			printf("FAILED\n");
		}
		free(result_array);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	testcases();
	getchar();
	return 0;
}