// S3Q9.cpp : Sum of elements in an array
//

#include "stdafx.h"

int length_of_array(int*input_array)
{
	int iter_loop=0;
	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

int sum_of_elements_array_one_way_recursion(int *input_array, int start_index)
{
	if(input_array==NULL)
	{
		printf("INVALID INPUT\n");
		return 0;
	}
	if(input_array[start_index]=='\0')
	{
		return 0;
	}
	if(input_array[start_index]!='\0')
	{
		return input_array[start_index]+sum_of_elements_array_one_way_recursion(input_array,start_index+1);
	}
}

int sum_of_elements_array_two_way_recursion(int *input_array, int start_index, int end_index)
{
	if(input_array==NULL)
	{
		printf("INVALID INPUT\n");
		return 0;
	}
	if(input_array[start_index]=='\0')
	{
		return 0;
	}
	if((start_index == end_index) && (input_array[start_index]!='\0'))
	{
		return input_array[start_index];
	}
	else if(!(start_index == end_index) && (input_array[start_index]!='\0'))
	{
		return (sum_of_elements_array_two_way_recursion(input_array,start_index,((start_index+end_index)/2)) 
			+ sum_of_elements_array_two_way_recursion(input_array,((start_index+end_index)/2)+1,end_index));
	}
}

void test_recursive_addition()
{
	int input_array[7][15] = {{1,2,3,4,5,6,7,8,9},{11,22,33,44,55,66,77,88,99},{1},{1,2,3},{1,2},{NULL}};
	int output_array[7] = {45,495,1,6,3,NULL};
	int iter_loop=0;
	for(iter_loop=0;iter_loop<6;iter_loop++)
	{
		(output_array[iter_loop] ==  sum_of_elements_array_one_way_recursion(input_array[iter_loop],0))?printf("ACCEPTED : "):printf("REJECTED : ");
		(output_array[iter_loop] ==  sum_of_elements_array_two_way_recursion(input_array[iter_loop],0,length_of_array(input_array[iter_loop])-1))?printf("ACCEPTED\n"):printf("REJECTED\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_recursive_addition();
	getchar();
	return 0;
}