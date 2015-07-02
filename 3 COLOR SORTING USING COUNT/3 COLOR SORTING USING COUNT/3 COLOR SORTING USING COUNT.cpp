// 3 COLOR SORTING USING COUNT.cpp : 3 COLOR SORTING USING COUNT OF EACH COLOR AND WRITING EXPLICITLY.
//

#include "stdafx.h"

int* three_color_sort(int *input_array, int length)
{
	if(input_array == NULL)
	{
		return NULL;
	}
	int iter_loop=0;
	int count_1=0, count_2=0, count_3=0;
	while(iter_loop<=length)
	{
		if(input_array[iter_loop]<1 || input_array[iter_loop]>3)
		{
			return NULL;
		}
		if(1==input_array[iter_loop])
		{
			count_1++;
		}
		if(2==input_array[iter_loop])
		{
			count_2++;
		}
		if(3==input_array[iter_loop])
		{
			count_3++;
		}
		iter_loop++;
	}
	if((count_1==0 && count_2==0) || (count_1==0 && count_3==0) || (count_3==0 && count_2==0))
	{
		return NULL;
	}
	iter_loop=0;
	while(count_1>0)
	{
		input_array[iter_loop] = 1;
		count_1--;
		iter_loop++;
	}
	while(count_2>0)
	{
		input_array[iter_loop] = 2;
		count_2--;
		iter_loop++;
	}
	while(count_3>0)
	{
		input_array[iter_loop] = 3;
		count_3--;
		iter_loop++;
	}
	return input_array;
}

int compare_arrays(int* input1, int *input2, int length)
{
	int iter_loop=0;
	while(iter_loop<length)
	{
		if(input1[iter_loop]!=input2[iter_loop])
		{
			return -1;
		}
		iter_loop++;
	}
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int input_array[10][20] = {
	{3,3,3,3,2,2,2,2,1,1,1,1},
	{1,1,1,1,1,1,1},
	{-1,1,1,1,2,3,2},
	{3,2,1},
	{1,1,3,2,2,2,1,1,3,2,1,1,3,2},
	{1},
	{2},
	{3},
	{NULL},
	{2,2,2,2,2,1}};

	int output_array[10][20] = {
		{1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3},
		{1,1,1,1,1,1,1},
		{-1,1,1,1,2,3,2},
		{1,2,3},
		{1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3},
		{1},
		{2},
		{3},
		{NULL},
		{1,2,2,2,2,2}};

	int length_of_inputs[11] = {12,7,7,3,14,1,1,1,1,6};
	for(int iter_loop=0;iter_loop<10;iter_loop++)
	{
		int *output = three_color_sort(input_array[iter_loop],length_of_inputs[iter_loop]-1);
		if(output==NULL)
		{
			printf("INVALID INPUT\n");
			continue;
		}
(compare_arrays(output,output_array[iter_loop],length_of_inputs[iter_loop]-1)==1)?printf("ACCEPTED\n"):printf("REJECTED\n");
	}
	getchar();
	return 0;
}