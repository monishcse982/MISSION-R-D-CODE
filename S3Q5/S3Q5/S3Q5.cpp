// S3Q5.cpp : Print all permutations from 1 to n numbers
//

#include "stdafx.h"
#include "stdlib.h"

int length_of_array(int *input_array)
{
	int length=0;
	while(input_array[length]!='\0')
	{
		length++;
	}
	return length;
}

void print_array(int *input_array)
{
	int iter_loop=0;
	while(input_array[iter_loop]!='\0')
	{
		printf("%d",input_array[iter_loop]);
		iter_loop++;
	}
	printf("\n");
}

void print_all_permutations(int *flag, int *initial_array, int *permutations_array, int current_position)
{
	if(initial_array==NULL)
	{
		printf("INVALID INPUT ARRAY.\n");
		return;
	}
	int array_length = length_of_array(initial_array), iter_loop=0;
	if(array_length == current_position)
	{
		print_array(permutations_array);
	}
	else if(array_length != current_position)
	{
		while(iter_loop<array_length)
		{
			if(flag[iter_loop]==0)
			{
				flag[iter_loop] = 1;
				permutations_array[current_position] = initial_array[iter_loop];
				print_all_permutations(flag, initial_array, permutations_array,  current_position+1);
				flag[iter_loop]=0;
			}
			iter_loop++;
		}
	}
}

void test_print_all_permutations()
{
	int input_array[5][6] = {{1,2},{1,2,3},{1,2,3,4},{1,2,3,4,5}};
	int iter_loop;
	for(iter_loop=0;iter_loop<4;iter_loop++)
	{
		int *permutations_array = (int*)calloc(length_of_array(input_array[iter_loop])+1,sizeof(int));
		int *flag = (int*)calloc(length_of_array(input_array[iter_loop])+1,sizeof(int));
		print_all_permutations(flag,input_array[iter_loop],permutations_array,0);
		printf("\n--------------------------------------------\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_print_all_permutations();
	getchar();
	return 0;
}