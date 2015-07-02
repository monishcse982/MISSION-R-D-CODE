// S1Q3.cpp : Given an integer array and length as inputs, write a function to remove all duplicate values in the same array (no second array). input array: 1,2,2,5,2,6,6,6,3,2,6,9, output array: 1,2,5,6,3,9
//

#include "stdafx.h"

void move_element_right(int *input, int element_position)
{
	int iter_loop = element_position;
	while(input[iter_loop+1]!='\0')
	{
		input[iter_loop] = input[iter_loop] + input[iter_loop+1];
		input[iter_loop+1] = input[iter_loop] - input[iter_loop+1];
		input[iter_loop] = input[iter_loop] - input[iter_loop+1];
		iter_loop++;
	}
	input[iter_loop] = '\0';
}

void remove_duplicates(int* input_array)
{
	int iter_loop=0, iter_loop2;
	while(input_array[iter_loop]!='\0')
	{
		iter_loop2 = iter_loop + 1;

		while(input_array[iter_loop2]!='\0')
		{
			if(input_array[iter_loop2] == input_array[iter_loop])
			{
				move_element_right(input_array, iter_loop2);
			}

			if(input_array[iter_loop2]!=input_array[iter_loop])
			{
				iter_loop2++;
			}
		}
		if(input_array[iter_loop+1]!=input_array[iter_loop])
		{
			iter_loop++;
			continue;
		}
			
		}
}

void test_remove_duplicates()
{
	int input_array[5][30] = {
								{1,2,2,5,2,6,6,6,3,2,6,9},
								{1,1,1,2,5,6,9,2,1,3,2,1,2,5,2,6,6,6,6,6,6,3,2,6,9},
								{1,2,3,5,4,3,1,2,4,5,4,4,2,1,3,4},
								{1,2,3,4,5,6},
								{1,1,1,1,1,1}
						     };
	int output_array[5][7] = {
								{1,2,5,6,3,9},
								{1,2,5,6,9,3},
								{1,2,3,5,4},
								{1,2,3,4,5,6},
								{1}
							 };
	int iter_loop,iter_loop2;
	for(iter_loop=0;iter_loop<5;iter_loop++)
	{
		remove_duplicates(input_array[iter_loop]);
		iter_loop2 = 0;
		while(input_array[iter_loop2] !='\0')
		{
			if(input_array[iter_loop][iter_loop2] != output_array[iter_loop][iter_loop2])
			{
				break;
			}
			else if(input_array[iter_loop][iter_loop2] == input_array[iter_loop][iter_loop2])
			{
				iter_loop2++;
				continue;
			}
		}
		if(input_array[iter_loop][iter_loop2] =='\0')
		{
			printf("ACCEPTED\n");
		}
		else if(input_array[iter_loop][iter_loop2] !='\0')
		{
			printf("REJECTED\n");
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	test_remove_duplicates();
	getchar();
	return 0;
}