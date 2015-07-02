// S3Q10.cpp : Find element in an unsorted array.
//

#include "stdafx.h"

int length_of_array(int *input_array)
{
	int iter_loop=0;
	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

int find_element_one_way_recursion(int* input_array, int key, int index)
{
	if(input_array==NULL)
	{
		printf("INVALID INPUT\n");
		return NULL;
	}
	else if(key==NULL)
	{
		printf("INVALID INPUT\n");
		return NULL;
	}
	else if(input_array[index+1]=='\0' && input_array[index]!=key)
	{
		printf("ELEMENT NOT FOUND");
		return -1;
	}
	else if(input_array[index]!='\0' && input_array[index] == key)
	{
		return index;
	}
	else if(input_array[index]!='\0' && input_array[index] != key)
	{
		return find_element_one_way_recursion(input_array,key,index+1);
	}
}

int find_element_two_way_recursion(int* input_array, int key, int start_index, int end_index)
{
	if(input_array==NULL)
	{
		printf("INVALID INPUT\n");
		return 0;
	}
	else if(key==NULL)
	{
		printf("INVALID INPUT\n");
		return 0;
	}
	else if(input_array[start_index]=='\0')
	{
		return NULL;
	}
	else if(input_array[start_index+1]=='\0' && start_index==end_index && input_array[start_index]!=key)
	{
		printf("ELEMENT NOT FOUND");
		return -1;
	}
	else if(input_array[start_index]!='\0' && start_index == end_index  && input_array[start_index]==key)
	{
		return start_index;
	}
	else if(input_array[start_index]!='\0' && start_index == end_index && input_array[start_index]!=key)
	{
		return 0;
	}
	else if((input_array[start_index]!='\0') && (start_index < end_index))
	{
		int result=find_element_two_way_recursion(input_array,key,start_index,((start_index+end_index)/2));
		if(result>0)
		{
			return result;
		}
		result =  find_element_two_way_recursion(input_array,key,((start_index+end_index)/2)+1,end_index);
		if(result>0)
		{
			return result;
		}
	}
}

void test_find_element()
{
	int input_array[6][10] = {{45,78,92},{46,87,24,97,2,5,84},{46,87,24,97,2,5,84},{45,78},{45}};
	int output_array[6] = {2,6,1,1,0};
	int key_elements[6] = {92,84,87,78,45};
	int iter_loop=0;
	for(iter_loop=0;iter_loop<5;iter_loop++)
	{
		(output_array[iter_loop]==find_element_one_way_recursion(input_array[iter_loop],key_elements[iter_loop],0))?printf("ACCEPTED : "):printf("REJECTED : ");
		(output_array[iter_loop]==find_element_two_way_recursion(input_array[iter_loop],key_elements[iter_loop],0,length_of_array(input_array[iter_loop])-1))?printf("ACCEPTED\n"):printf("REJECTED\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_find_element();
	getchar();
	return 0;
}