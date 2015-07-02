// S5Q4.cpp : Given a binary tree with left, right pointers and also parent pointer, given any TREE_NODE write program to find height of the TREE_NODE. root is given as input as well to the function
//

#include "stdafx.h"
#include "stdlib.h"

struct TREE_NODE
{
	int data;
	TREE_NODE *left_child;
	TREE_NODE *right_child;
	TREE_NODE *parent;
};

TREE_NODE* find_the_TREE_NODE(TREE_NODE *root, int key)
{
	if(root->data == key)
	{
		return root;
	}
	if(root->left_child == NULL && root->right_child == NULL)
	{
		return NULL;
	}
	if(root->left_child!=NULL)
	{
		TREE_NODE *temp = find_the_TREE_NODE(root->left_child,key);
		if(temp!=NULL && temp->data == key)
		{
			return temp;
		}
	}

	if(root->right_child!=NULL)
	{
		TREE_NODE *temp = find_the_TREE_NODE(root->right_child,key);
		if(temp!=NULL && temp->data == key)
		{
			return temp;
		}
	}

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

int construct_tree(TREE_NODE* root, char *input_string, int index)
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
		TREE_NODE *temp = (TREE_NODE*)malloc(sizeof(TREE_NODE));
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
		TREE_NODE *temp = (TREE_NODE*)malloc(sizeof(TREE_NODE));
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

int string_length(char* input_array)
{
	int iter_loop=0;

	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

void delete_tree(TREE_NODE *root)
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

int find_height(TREE_NODE *root, int height)
{
	int height_of_left_child=0,height_of_right_child=0;
	if(root->left_child!=NULL)
	{
		height_of_left_child = find_height(root->left_child,height);
	}
	if(root->right_child!=NULL)
	{
		height_of_right_child = find_height(root->right_child,height);
	}
	if(root->left_child==NULL && root->right_child==NULL)
	{
		height = 0;
		return height;
	}
	if(height_of_left_child>height_of_right_child)
	{
		height = height_of_left_child+1;
	}
	else if(height_of_left_child<height_of_right_child)
	{
		height = height_of_right_child+1;
	}
	else if(height_of_left_child==height_of_right_child)
	{
		height = height_of_left_child+1;
	}
	return height;
}

int calculate_height_of_the_node(TREE_NODE *root, int key)
{
	TREE_NODE *key_node = find_the_TREE_NODE(root,key);
	return (find_height(key_node,0));
}

void test_height_of_node()
{
	char input[4][77] = {"5,2,1,$,3,-,4,$,7,6,$,8,-,9,$",
						"10,5,2,1,$,3,-,4,$,7,6,$,8,-,9,$,15,12,11,$,13,-,14,$,18,16,-,17,$,19,-,20,$",
						"8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$",
						"6,3,1,-,2,$,4,-,5,$,9,7,-,8,$,10,-,11,$"};
	int key_node[4][10] = {{1,9,4,3,5,6,2,7,8},{12,13,1,4,2,7,9,16,20},{1,2,15,7,4,9,10,3,6},{4,6,1,3,7,9,2,11,10}};
	int expected_output[4][10] = {{0,0,0,1,3,0,2,2,1},{2,1,0,0,2,2,0,1,0},{0,1,0,0,2,0,1,0,1},{1,3,1,2,1,2,0,0,1}};
	int iter_loop1, iter_loop2,iter_loop3;
	for(iter_loop1=0;iter_loop1<3;iter_loop1++)
	{
		TREE_NODE *root = (TREE_NODE*)malloc(sizeof(TREE_NODE));
			int index;
			index = next_element_in_string(input[iter_loop1],0);
			root->data = create_number(input[iter_loop1],index);
			index = next_element_in_string(input[iter_loop1],index);
			construct_tree(root,input[iter_loop1],index);
		for(iter_loop2=0;iter_loop2<9;iter_loop2++)
		{
			printf("%d->",iter_loop2+1);
(expected_output[iter_loop1][iter_loop2] == calculate_height_of_the_node(root,key_node[iter_loop1][iter_loop2]))?printf("ACCEPTED\n"):printf("REJECTED\n");
		}
		printf("<==========>\n");
		delete_tree(root);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_height_of_node();
	getchar();
	return 0;
}