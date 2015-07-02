// LEAST COMMON ANCESTOR WITH ARRAYS.cpp : Defines the entry point for the console application.
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

int* route_to_node(NODE* root, NODE *node, int *route_of_node, int *index, int *size)
{
	if(root->data == node->data)
	{
		route_of_node = (int*)realloc(route_of_node,(*size+1)*sizeof(int));
		route_of_node[*index] = root->data;
		return route_of_node;
	}
	else if(root->data != node->data && (root->left_child!=NULL || root->right_child!=NULL))
	{
		route_of_node = (int*)realloc(route_of_node,(*size+1)*sizeof(int));
		route_of_node[*index] = root->data;
		*index = *index+1;
		*size = *size+1;
	}
	else if(root->data != node->data && root->left_child==NULL && root->right_child==NULL)
	{
		return route_of_node;
	}
	if(root->left_child!=NULL)
	{
		route_of_node = route_to_node(root->left_child,node,route_of_node,index,size);
		if(route_of_node[*index]==node->data)
		{
			return route_of_node;
		}
		route_of_node[*index] = '\0';
	}
	if(root->right_child!=NULL)
	{
		route_of_node = route_to_node(root->right_child,node,route_of_node,index,size);
		if(route_of_node[*index]==node->data)
		{
			return route_of_node;
		}
		route_of_node[*index] = '\0';
	}
	if(route_of_node[*index]!=node->data)
		{
			route_of_node[*index-1] = '\0';
			*index = *index-1;
			return route_of_node;
		}
}

int find_least_common_ancestor(NODE *root, NODE *node1, NODE *node2)
{
	int *route1 =(int*)malloc(1*sizeof(int));
	int index = 0, size=1;
	route1 = route_to_node(root,node1,route1,&index,&size);
	route1[index+1]='\0';
	index =0; size=1;
	int *route2 =(int*)malloc(1*sizeof(int));
	route2 = route_to_node(root,node2,route2,&index,&size);
	route2[index+1]='\0';
	
	int iter_loop=0;
	while(route1[iter_loop]!='\0' && route2[iter_loop]!='\0')
	{
		if(route1[iter_loop] == route2[iter_loop])
		{
			iter_loop++;
			continue;
		}
		else if((route1[iter_loop] != route2[iter_loop]) &&(route1[iter_loop-1] == route2[iter_loop-1]))
		{
			return route1[iter_loop-1];
		}
	}
	if(route1[iter_loop]=='\0' && route2[iter_loop]!='\0')
	{
		return route1[iter_loop-1];
	}
	else if(route2[iter_loop]=='\0' && route1[iter_loop]!='\0')
	{
		return route2[iter_loop-1];
	}
}

void driver_for_convert_string_to_tree(char *string)
{
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
		getchar();
		return;
	}
	printf("LCA IS: %d\n",find_least_common_ancestor(root,node1,node2));
	getchar();
	delete_tree(root);
}

int _tmain(int argc, _TCHAR* argv[])
{
	char string[98] = "([1,1],[2,1],[4,2],[8,4],[9,4],[5,2],[10,5],[11,5],[3,1],[6,3],[12,6],[13,6],[7,3],[14,7],[15,7])";
	driver_for_convert_string_to_tree(string);
	getchar();
	return 0;
}

