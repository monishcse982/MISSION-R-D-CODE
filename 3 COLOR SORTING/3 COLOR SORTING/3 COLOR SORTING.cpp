// 3 COLOR SORTING.cpp : SORT AN ARRAY IN ASCENDING ORDER WHICH CONTATINS ONLY 1's 2's 3's.
//

#include "stdafx.h"

int three_color_sort(int *input_array, int length)
{
	int iter_loop=0, count_1=0,count_2=0,count_3=0;
	while(iter_loop<=length)
	{
		if(input_array[iter_loop]<1 || input_array[iter_loop]>3)
		{
			return NULL;
		}
		if(input_array[iter_loop]==1 && count_1==0)
		{
			count_1++;
		}
		if(input_array[iter_loop]==2 && count_2==0)
		{
			count_2++;
		}
		if(input_array[iter_loop]==3 && count_3==0)
		{
			count_3++;
		}
		iter_loop++;
	}
	if((count_1+count_2+count_3)<2)
	{
		return NULL;
	}
	int left_pointer, right_pointer, current_pointer,case_variable;
	current_pointer = left_pointer = 0;
	right_pointer = length;
	while(input_array[left_pointer]==1)
	{
		left_pointer++;
		current_pointer++;
	}
	while(input_array[right_pointer]==3)
	{
		right_pointer--;
	}
	while(current_pointer<=right_pointer && current_pointer<=length)
	{
		switch (input_array[current_pointer])
		{
		case 1:
			{
				int temp = input_array[left_pointer];
				input_array[left_pointer] = input_array[current_pointer];
				input_array[current_pointer] = temp;
				while(input_array[left_pointer]==1)
				{
					left_pointer++;
				}
				current_pointer++;
				break;
			}
		case 2:
			{
				current_pointer++;
				break;
			}
		case 3:
			{
				int temp = input_array[right_pointer];
				input_array[right_pointer] = input_array[current_pointer];
				input_array[current_pointer] = temp;
				while(input_array[right_pointer]==3)
				{
					right_pointer--;
				}
				if((current_pointer == right_pointer) && (input_array[current_pointer]==input_array[right_pointer]==1))
				{
					int temp = input_array[left_pointer];
					input_array[left_pointer] = input_array[current_pointer];
					input_array[current_pointer] = temp;
				}
				break;
			}
		default:
			break;
		}
	}
}

int compare_arrays(int* input1, int *input2, int length)
{
	int iter_loop=0;
	while(iter_loop<=length)
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

	int length_of_inputs[10] = {12,7,7,3,14,1,1,1,1,6};
	for(int iter_loop=0;iter_loop<10;iter_loop++)
	{
		if(three_color_sort(input_array[iter_loop],length_of_inputs[iter_loop]-1)==NULL)
		{
			printf("INVALID INPUT\n");
			continue;
		}
		(compare_arrays(input_array[iter_loop],output_array[iter_loop],length_of_inputs[iter_loop]-1)==1)?printf("ACCEPTED\n"):printf("REJECTED\n");
	}
	getchar();
	return 0;
}