// S5Q1.cpp : Given a string with comma seperated values(unsorted), create a binary tree
//


#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *previous;
	NODE *next;
};

int tree_comparator(NODE *root1, NODE *root2)
{
	if(root1 == NULL && root2 == NULL)
	{
		printf("EMPTY\n");
		return 1;
	}
	if((root1 == NULL && root2!=NULL) || (root1 != NULL && root2==NULL))
	{
		return -1;
	}
	if(root1->data!=root2->data)
	{
		return -1;
	}
	else if((root1->previous!=NULL && root2->previous==NULL) || (root1->previous==NULL && root2->previous!=NULL))
	{
		return -1;
	}
	else if((root1->next!=NULL && root2->next==NULL) || (root1->next==NULL && root2->next!=NULL))
	{
		return -1;
	}

	if(root1->previous!=NULL && root2->previous!=NULL)
	{
		int result = tree_comparator(root1->previous,root2->previous);
		if(result==-1)
		{
			return -1;
		}
	}

	if(root1->next!=NULL && root2->next!=NULL) 
	{
		int result = tree_comparator(root1->next,root2->next); 
		if(result==-1)
		{
			return -1;
		}
	}
	return 1;
}

int next_element_in_string(char *input, int index)
{
	if(input[index]=='\0')
	{
		return NULL;
	}
	if(input[index]==',')
	{
		index++;
	}
	while(input[index]!='\0' && input[index]!=',')
	{
		index++;
	}
	return index;
}

int exponent(int base, int power)
{
	if(power == 0)
	{
		return 1;
	}
	int result=1, iter_loop;
	for(iter_loop=0;iter_loop<power;iter_loop++)
	{
		result *= base;
	}
	return result;
}

int create_number(char *input_array, int start)
{
	int negative_flag=0;
	if(input_array[start]=='\0')
	{
		return NULL;
	}
	int iter_loop = start-1,result=0,power=0;
	while(iter_loop>=0 && input_array[iter_loop]!=',')
	{
		if(input_array[iter_loop]=='-' && ((input_array[iter_loop+1]>='0' && input_array[iter_loop+1]<='9')))
		{
			negative_flag++;
			iter_loop--;
			continue;
		}
		if(!(input_array[iter_loop]>='0' && input_array[iter_loop]<='9'))
		{
			return NULL;
		}
		result += (input_array[iter_loop] & ('p'-'a')) * exponent(10,power);
		power++;
		iter_loop--;
	}
	if(negative_flag==1)
	{
		return 0-result;
	}
	return result;
}

int construct_tree(NODE* root, char *input_string, int index)
{
	if(input_string == NULL)
	{
		return NULL;
	}
	if(input_string[index-1]=='\0' || input_string[index-1]=='$')
	{
		root->previous = NULL;
		root->next = NULL;
		return index;
	}
	int result;
	result = create_number(input_string,index);
	if(result!=NULL)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		temp->data = result;
		root->previous = temp;
	}
	else if(result==NULL)
	{
		root->previous = NULL;
	}
	if(root->previous!=NULL)
	{
		index = next_element_in_string(input_string,index);
		index = construct_tree(root->previous,input_string,index);
	}
	index = next_element_in_string(input_string,index);
	result = create_number(input_string,index);
	if(result!=NULL)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		temp->data = result;
		root->next = temp;
	}
	else if(result==NULL)
	{
		root->next = NULL;
	}
	if(root->next!=NULL)
	{
		index = next_element_in_string(input_string,index);
		index = construct_tree(root->next,input_string,index);
		return index;
	}
	else if(root->next==NULL)
	{
		return index;
	}
}

int string_length(char* input_array)
{
	int iter_loop=0;

	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

int array_length(int *input_array)
{
	int iter_loop=0;

	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

int* string_to_array(char *input_array)
{
	int length = string_length(input_array)-1, result_integer=0, iter_loop = length,negative_input_flag=0, size=0;

	while(input_array[result_integer]!='\0')
	{
		if(input_array[result_integer]==',')
		{
			size++;
		}
		result_integer++;
	}
	int *output_array = (int*)malloc((size+2)*sizeof(int));
	output_array[size+1] = '\0';
	while(iter_loop>=0)
	{
			result_integer = 0;
			int power=0;
		while (input_array[iter_loop]!=',' && iter_loop>=0)
		{
			if(input_array[iter_loop] == '-' && (input_array[iter_loop-1]==',' || iter_loop==0))
			{
				negative_input_flag++;
				break;
			}
			else if(input_array[iter_loop]<'0' && input_array[iter_loop]>'9')
			{
			break;
			}
			result_integer += (input_array[iter_loop] & ('p'-'a')) * exponent(10,power);
			iter_loop--;
			power++;
		}
		if(iter_loop>=-1 || input_array[iter_loop]==',')
		{
			if(negative_input_flag==1)
			{
				output_array[size] = (-result_integer);
			}
			else if(negative_input_flag==0)
			{
				output_array[size] = result_integer;
			}
			negative_input_flag = 0;
			size--;
		}
		while(iter_loop>0 && input_array[iter_loop]!=',')
		{
			iter_loop--;
		}
		iter_loop--;
	}
	return output_array;
}

NODE* array_to_tree_convertor(int *input_array, int start, int end)
{
	if(start > end)
	{
		return NULL;
	}
	if(start == end)
	{
		return NULL;
	}
	int mid = (start + end)/2;
	NODE *root = (NODE*)malloc(sizeof(NODE));
	root->data = input_array[mid];
	root->previous = array_to_tree_convertor(input_array, start, mid);
	if(root->previous!=NULL && root->previous->data == root->data)
	{
		root->previous = NULL;
	}
	root->next = array_to_tree_convertor(input_array, mid+1, end);
	if(root->next!=NULL && root->next->data == root->data)
	{
		root->next = NULL;
	}
	return root;
}

void delete_tree(NODE *root)
{
	if(root->previous!=NULL)
	{
		delete_tree(root->previous);
	}

	if(root->next!=NULL)
	{
		delete_tree(root->next);
	}

	free(root);
}

NODE* string_to_tree_converter(char *input_array)
{
	int *integer_array = string_to_array(input_array);
	NODE* output =  array_to_tree_convertor(integer_array,0,array_length(integer_array));
	free(integer_array);
	return output;
}

void test_array_to_tree_convertor()
{
	char input[5][36] = {"1","1,4,2,3","2,1","3,1,2","2,4,6,1,8,10,12,14,15,3,5,13,7,9,11"};
	char output[5][52] = {   
					  "1,$",
					  "2,4,1,$,-,3,$",
					  "1,2,$,-",
					  "1,3,$,2,$",
					  "14,1,4,2,$,6,$,10,8,$,12,$,13,3,15,$,5,$,9,7,$,11,$"
					 };
	int iter_loop, index;
	for(iter_loop=0;iter_loop<=4;iter_loop++)
	{
		printf("%d-->",iter_loop+1);
		NODE *root1 = string_to_tree_converter(input[iter_loop]);
		NODE *root2 = (NODE*)malloc(sizeof(NODE));

		index = next_element_in_string(output[iter_loop],0);
		root2->data = create_number(output[iter_loop],index);
		index = next_element_in_string(output[iter_loop],index);
		construct_tree(root2,output[iter_loop],index);

		(tree_comparator(root1,root2) == 1)?(printf("ACCEPTED\n")):(printf("REJECTED\n"));
		delete_tree(root1);
		delete_tree(root2);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_array_to_tree_convertor();
	getchar();
	return 0;
}