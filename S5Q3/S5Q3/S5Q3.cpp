// S5Q3.cpp : Given a binary tree as input write program to check whether its a binary search tree or not
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *left;
	NODE *right;
};

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
		root->left = NULL;
		root->right = NULL;
		return index;
	}
	int result;
	result = create_number(input_string,index);
	if(result!=NULL)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		temp->data = result;
		root->left = temp;
	}
	else if(result==NULL)
	{
		root->left = NULL;
	}
	if(root->left!=NULL)
	{
		index = next_element_in_string(input_string,index);
		index = construct_tree(root->left,input_string,index);
	}
	index = next_element_in_string(input_string,index);
	result = create_number(input_string,index);
	if(result!=NULL)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		temp->data = result;
		root->right = temp;
	}
	else if(result==NULL)
	{
		root->right = NULL;
	}
	if(root->right!=NULL)
	{
		index = next_element_in_string(input_string,index);
		index = construct_tree(root->right,input_string,index);
		return index;
	}
	else if(root->right==NULL)
	{
		return index;
	}
}

int Inorder(NODE *root, int *previous_value)
{
	if(root->left!=NULL)
	{
		if(0 == Inorder(root->left,previous_value))
		{
			return 0;
		}
	}

	if(*previous_value == NULL)
	{
		*previous_value = root->data;
	}
	else if(*previous_value!=NULL)
	{
		if(*previous_value>root->data)
		{
			*previous_value = root->data;
			return 0;
		}
		*previous_value = root->data;
	}

	if(root->right!=NULL)
	{
		if(0 == Inorder(root->right,previous_value))
		{
			return 0;
		}
	}
	return 1;
}

void delete_tree(NODE *root)
{
	if(root->left!=NULL)
	{
		delete_tree(root->left);
	}

	if(root->right!=NULL)
	{
		delete_tree(root->right);
	}

	free(root);
}

void check_if_BST()
{
	char input[5][52] = {   
					  "1,$",
					  "2,3,$,1,-,4,$",
					  "1,-,2,$",
					  "2,1,$,3,$",
					  "8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$"
					 };
	int expected_output[6] = {1,0,1,1,1};
	int iter_loop, index;
	for(iter_loop=0;iter_loop<=4;iter_loop++)
	{
		NODE *root = (NODE*)malloc(sizeof(NODE));
		index = next_element_in_string(input[iter_loop],0);
		root->data = create_number(input[iter_loop],index);
		index = next_element_in_string(input[iter_loop],index);
		construct_tree(root,input[iter_loop],index);
		
		int previous_value = NULL;
		(expected_output[iter_loop]==Inorder(root,&previous_value))?printf("ACCEPTED\n"):printf("REJECTED\n");
		delete_tree(root);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	check_if_BST();
	getchar();
	return 0;
}