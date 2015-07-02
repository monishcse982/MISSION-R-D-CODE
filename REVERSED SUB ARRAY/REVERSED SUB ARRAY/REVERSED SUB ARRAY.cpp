// REVERSED SUB ARRAY.cpp : TWO SUBARRAYS ARE REVERSED FIX THEM TO GET THE SORTED ARRAY
//

#include "stdafx.h"

void array_reverse(int *input_array, int start, int end)
{
	while(start<=end)
	{
		int temp = input_array[start];
		input_array[start] = input_array[end];
		input_array[end] = temp;
		start++;
		end--;
	}
}

void print_array(int *input)
{
	int iter_loop=0;
	while(input[iter_loop]!='\0')
	{
		printf("%d ",input[iter_loop]);
		iter_loop++;
	}
}

int check_if_sorted(int *input)
{
	if(input == NULL)
	{
		return NULL;
	}
	int iter_loop=0;
	while(input[iter_loop+1]!='\0')
	{
		if(input[iter_loop-1] > input[iter_loop])
		{
			return -1;
		}
		iter_loop++;
	}
	return 1;
}

int length_of_array(int *input_array)
{
	int iter_loop=0;
	while(input_array[iter_loop])
	{
		iter_loop++;
	}
	return iter_loop++;
}

int reversed_sub_arrays(int *input_array)
{
	int length = length_of_array(input_array);
	if(input_array== NULL)
	{
		return -1;
	}
	int iter_loop=0, start_of_reverse=-1, end_of_reverse=-1,start_of_reverse2=-1, end_of_reverse2=-1;
	while(iter_loop!=length-1)
	{
		if(start_of_reverse==-1 && iter_loop+1!=length-1 && input_array[iter_loop]>input_array[iter_loop+1])
		{
			start_of_reverse = iter_loop;
		}
		if(start_of_reverse!=-1 && input_array[iter_loop]>input_array[start_of_reverse])
		{
			end_of_reverse = iter_loop-1;
			break;
		}
		else if(start_of_reverse!=-1 && iter_loop+1!=length-1)
		{
			end_of_reverse = iter_loop;
			break;
		}
		iter_loop++;
	}
	if(start_of_reverse==-1)
	{
		return -1;
	}
	while(iter_loop!=length-1)
	{
		if(start_of_reverse2==-1 && iter_loop+1!=length-1 && input_array[iter_loop]>input_array[iter_loop+1])
		{
			start_of_reverse2 = iter_loop;
		}
		if(start_of_reverse2!=-1 && input_array[iter_loop]>input_array[start_of_reverse2])
		{
			end_of_reverse2 = iter_loop-1;
			break;
		}
		else if(start_of_reverse2!=-1 && iter_loop+1==length-1)
		{
			end_of_reverse2 = iter_loop;
			break;
		}
		iter_loop++;
	}
	if(start_of_reverse2==-1)
	{
		return -1;
	}
	while(iter_loop!=length-1)
	{
		if(iter_loop+1!=length-1 && input_array[iter_loop]>input_array[iter_loop+1])
		{
			return -1;
		}
		iter_loop++;
	}
	array_reverse(input_array,start_of_reverse,end_of_reverse);
	array_reverse(input_array,start_of_reverse2,end_of_reverse2);
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int input_array[9][20] = {{1,4,3,2,5,9,8,7,6},{2,1,5,4,3},{1,2,3},{2,1,3,4,5,6,7,9,8},{NULL},{1,2,3,4,5,6,7,8,9},{3,2,1,4,5,9,8,7,6},{2,1,3,4,5,7,6},{2,1,3,4,5,7,6,8,9,11,10}};
	for(int iter_loop=0;iter_loop<9;iter_loop++)
	{
		if(reversed_sub_arrays(input_array[iter_loop])==-1)
		{
			printf("%d--->INVALID INPUT\n",iter_loop+1);
			continue;
		}
		(1==check_if_sorted(input_array[iter_loop]))?printf("%d-->ACCEPTED\n",iter_loop+1):printf("%d-->REJECTED\n",iter_loop+1);
	}
	getchar();
	return 0;
}