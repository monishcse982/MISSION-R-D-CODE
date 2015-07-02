// S2Q9.cpp : Given an array which is not sorted, write a search function. given a number write a function (with test stubs and main too :-)) to find the number in the array
//

#include "stdafx.h"

int linear_search(int *input_array, int search_key)
{
	int iter_loop=0;
	while(input_array[iter_loop]!='\0')
	{
		if(input_array[iter_loop]== search_key)
		{
			return iter_loop;
		}
		iter_loop++;
	}
}

void test_linear_search()
{
	int input_array[4][10] = {{95,85,495,485,584,385,5854,284,589,63},{5,3,7,12,87,39,4,8,25,46},{345},{56,495,584}};
	int search_keys[4] = {385,46,345,9};
	int output_array[4] = {5,9,0,NULL};
	int iter_loop=0;
	int no_of_inputs = 4;
	for(iter_loop=0;iter_loop<no_of_inputs;iter_loop++)
	{
		int result = linear_search(input_array[iter_loop],search_keys[iter_loop]);
		if(output_array[iter_loop] == result)
		{
			printf("FOUND\n");
		}
		else if(output_array[iter_loop]!=result)
		{
			printf("NOT FOUND\n");
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_linear_search();
	getchar();
	return 0;
}