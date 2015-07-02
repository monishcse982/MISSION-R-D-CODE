// S3Q8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *left_child;
	NODE *right_child;
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
	else if((root1->left_child!=NULL && root2->left_child==NULL) || (root1->left_child==NULL && root2->left_child!=NULL))
	{
		return -1;
	}
	else if((root1->right_child!=NULL && root2->right_child==NULL) || (root1->right_child==NULL && root2->right_child!=NULL))
	{
		return -1;
	}

	if(root1->left_child!=NULL && root2->left_child!=NULL)
	{
		int result = tree_comparator(root1->left_child,root2->left_child);
		if(result==-1)
		{
			return -1;
		}
	}

	if(root1->right_child!=NULL && root2->right_child!=NULL) 
	{
		int result = tree_comparator(root1->right_child,root2->right_child); 
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
		root->left_child = NULL;
		root->right_child = NULL;
		return index;
	}
	int result;
	result = create_number(input_string,index);
	if(result!=NULL)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		temp->data = result;
		root->left_child = temp;
	}
	else if(result==NULL)
	{
		root->left_child = NULL;
	}
	if(root->left_child!=NULL)
	{
		index = next_element_in_string(input_string,index);
		index = construct_tree(root->left_child,input_string,index);
	}
	index = next_element_in_string(input_string,index);
	result = create_number(input_string,index);
	if(result!=NULL)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		temp->data = result;
		root->right_child = temp;
	}
	else if(result==NULL)
	{
		root->right_child = NULL;
	}
	if(root->right_child!=NULL)
	{
		index = next_element_in_string(input_string,index);
		index = construct_tree(root->right_child,input_string,index);
		return index;
	}
	else if(root->right_child==NULL)
	{
		return index;
	}
}

void delete_tree(NODE *root)
{
	if(root->left_child!=NULL)
	{
		delete_tree(root->left_child);
	}

	if(root->right_child!=NULL)
	{
		delete_tree(root->right_child);
	}

	free(root);
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

int size_of_tree(NODE *root, int size)
{
	if(root->left_child!=NULL)
	{
		size = size_of_tree(root->left_child,size);
	}
	size++;
	if(root->right_child!=NULL)
	{
		size = size_of_tree(root->right_child,size);
	}
	return size;
}

int Preorder_traversal(NODE *root, int index, int *traversal_array)
{
	traversal_array[index] = root->data;
	index++;
	if(root->left_child!=NULL)
	{
		index = Preorder_traversal(root->left_child,index,traversal_array);
	}

	if(root->right_child!=NULL)
	{
		index = Preorder_traversal(root->right_child,index,traversal_array);
	}
	return index;
}

int compare_arrays(int *array_1, int *array_2)
{
	for(int iter_loop=0;array_1[iter_loop]!='\0'||array_2[iter_loop]!='\0';iter_loop++)
	{
		if(array_1[iter_loop]!=array_2[iter_loop])
		{
			return -1;
		}
	}
	return 1;
}

int* driver_of_traverse_arrays(NODE *root)
{
	if(root==NULL)
	{
		return NULL;
	}
	int size = size_of_tree(root,0);
	int *traversal_array = (int*)malloc((size+1)*sizeof(int));
	traversal_array[size] = '\0';
	Preorder_traversal(root,0,traversal_array);
	return traversal_array;
}

void test_traversal()
{
	char input[10][53] = {"8,-4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$",
								  "8,4,2,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$",
								  "8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,-",
								  "5,4,2,$,1,$,3,6,$,7,$",
								  "5,4,$,3,6,$,7,$",
								  "5,4,2,$,1,$,3,$",
								  "1,2,$,3,$",
								  "5,$",
								  "1,2,$,-",
								  '\0'
								};

	int output[10][16] ={
						{8,-4,2,1,3,6,5,7,12,10,9,11,14,13,15},
						{8,4,2,6,5,7,12,10,9,11,14,13,15},
						{8,4,2,1,3,6,5,7,12,10,9,11},
						{5,4,2,1,3,6,7},
						{5,4,3,6,7},
						{5,4,2,1,3},
						{1,2,3},
						{5},
						{1,2},
						NULL
						}; 
	int iter_loop;
	for(iter_loop=0;iter_loop<10;iter_loop++)
	{
		int index;
		NODE *root = (NODE*)malloc(sizeof(NODE));

		index = next_element_in_string(input[iter_loop],0);
		root->data = create_number(input[iter_loop],index);
		index = next_element_in_string(input[iter_loop],index);
		construct_tree(root,input[iter_loop],index);

		int *traversal_array;
		traversal_array = driver_of_traverse_arrays(root);
		(compare_arrays(traversal_array,output[iter_loop]) == 1)?printf("ACCEPTED\n"):printf("REJECTED\n");
		free(traversal_array);
		delete_tree(root);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_traversal();
	getchar();
	return 0;
}