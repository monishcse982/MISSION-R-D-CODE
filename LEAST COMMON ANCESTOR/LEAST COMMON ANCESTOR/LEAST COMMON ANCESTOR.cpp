// LEAST COMMON ANCESTOR.cpp : FIND THE LEAST COMMON ANCESTOR OF TWO NODES IN A BST.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE* left_child;
	NODE* right_child;
};

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

int* count_delimiters(char *string)
{
	int iter_loop,size=1,index=0;
	int *position_of_delimiters = (int*)malloc(1*sizeof(int));
	for(iter_loop=0;string[iter_loop]!='\0';iter_loop++)
	{
		if(string[iter_loop]==']')
		{
			if(index!=0)
			{
				position_of_delimiters = (int*) realloc(position_of_delimiters,((size+1)*sizeof(int)));
				size++;
				position_of_delimiters[index] = iter_loop;
				index++;
			}
			else if(index==0)
			{
				position_of_delimiters[index]= iter_loop;
				index++;
			}
		}
	}
	position_of_delimiters = (int*) realloc(position_of_delimiters,((size+1)*sizeof(int)));
	position_of_delimiters[size] = '\0';
	return position_of_delimiters;
}

int* string_to_integer(char *input_array, int start)
{
	if(input_array[start]=='\0')
	{
		return NULL;
	}
	int *output_number = (int*)malloc(3*sizeof(int));
	output_number[2] ='\0'; 
	int result=0,power=0;
	while(input_array[start]!='[')
	{
		result=power=0;
		start = start-1;
		while(input_array[start]!='[' && input_array[start]!=',')
		{
			result += (input_array[start] & ('p'-'a')) * exponent(10,power);
			power++;
			start--;
		}
		if(input_array[start]==',')
		{
			output_number[0] = result;
		}
		else if(input_array[start]=='[')
		{
			output_number[1] = result;
		}
	}
	return output_number;
}

int convert_string_to_tree(char *string, int index, int *position_of_delimiters, NODE *root)
{
	if(position_of_delimiters[index]=='\0')
	{
		return index;
	}
	int *return_numbers = string_to_integer(string,position_of_delimiters[index]);
	if(return_numbers[0]==return_numbers[1])
	{
		root->data = return_numbers[0];
		root->left_child = root->right_child = NULL;
		index++;
		index = convert_string_to_tree(string, index,position_of_delimiters,root);
		index = convert_string_to_tree(string, index,position_of_delimiters,root);
		free(return_numbers);
		return index;
	}
	else if(return_numbers[0]!=root->data)
	{
		free(return_numbers);
		return index;
	}
	else if(return_numbers[0]!=return_numbers[1])
	{
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		new_node->data = return_numbers[1];
		new_node->left_child = NULL;
		new_node->right_child = NULL;
		if(root->left_child==NULL)
		{
			root->left_child = new_node;
			index++;
		}
		else if(root->right_child==NULL)
		{
			root->right_child = new_node;
			index++;
		}
		index = convert_string_to_tree(string, index,position_of_delimiters,new_node);
		index = convert_string_to_tree(string, index,position_of_delimiters,new_node);
		free(return_numbers);
		return index;
	}
}

NODE* find_node(NODE *root, int key)
{
	if(root->data==key)
	{
		return root;
	}
	if(root->left_child!=NULL)
	{
		NODE *temp = find_node(root->left_child,key);
		if(temp!=NULL && temp->data == key)
		{
			return temp;
		}
	}
	if(root->right_child!=NULL)
	{
		NODE *temp = find_node(root->right_child,key);
		if(temp!=NULL &&temp==NULL)
		{
			return NULL;
		}
	}
	else if(root->data!=key)
	{
		return NULL;
	}
}

NODE* find_least_common_ancestor(NODE* root, NODE *node1, NODE *node2)
{
	if(root->data==node1->data || root->data == node2->data)
	{
		return root;
	}
	if(root->data==node1->data && root->data==node2->data)
	{
		return root;
	}
	if((node1->data<root->data && node2->data>root->data) || (node2->data<root->data && node1->data>root->data))
	{
		return root;
	}
	
	if((node1==node2) && (root!=node1))
	{
		return node1;
	}
	if((node1->data==root->data && (node2->data<root->data || node2->data>root->data)))
	{
		return node1;
	}
	if((node2->data==root->data && (node1->data<root->data || node1->data>root->data)))
	{
		return node2;
	}
	if(node1->data<root->data && node2->data<root->data)
	{
		find_least_common_ancestor(root->left_child,node1,node2);
	}
	if(node1->data>root->data && node2->data>root->data)
	{
		find_least_common_ancestor(root->right_child,node1,node2);
	}

	if(root->left_child!=NULL)
	{
		NODE *node = find_least_common_ancestor(root->left_child,node1,node2);
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

void driver_for_convert_string_to_tree()
{
	printf("INPUT THE A BST IN THE FOLLOWINT FORMAT:\n FOR A TREE WITH 1 AS ROOT AND 2&3 AS ITS LEFT AND RIGHT CHILDREN ENTER THE INPUT AS\n([1,1],[2,1],[3,1])\n");
	char *string = (char*)malloc(1024*sizeof(char));
	gets_s(string,1024);
	int *position_of_delimiters = count_delimiters(string);
	NODE *root = (NODE*)malloc(sizeof(NODE));
	convert_string_to_tree(string,0,position_of_delimiters,root);
	free(position_of_delimiters);
	int node1_value, node2_value;
	printf("ENTER THE NODE VALUES:\n");
	scanf_s("%d",&node1_value);
	scanf_s("%d",&node2_value);
	NODE *node1 = find_node(root, node1_value);
	NODE *node2 = find_node(root,node2_value);
	if(node1==NULL || node2==NULL)
	{
		printf("INVALID INPUT");
		return;
	}
	printf("LEAST COMMON ANCESTOR IS %d\n",find_least_common_ancestor(root,node1,node2)->data);
	delete_tree(root);
	free(string);
}

int _tmain(int argc, _TCHAR* argv[])
{
	driver_for_convert_string_to_tree();
	getchar();
	return 0;
}