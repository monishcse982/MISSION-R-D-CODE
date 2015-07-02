// S5Q7.cpp : Defines the entry point for the console application.
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

int string_length(char* input_array)
{
	int iter_loop=0;

	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
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

void Inorder(NODE *root)
{
	if(root->left_child!=NULL)
	{
		Inorder(root->left_child);
	}
	printf("%d ",root->data);
	if(root->right_child!=NULL)
	{
		Inorder(root->right_child);
	}
}

NODE* driver_for_convert_string_to_tree(char *string)
{
	int *position_of_delimiters;
	position_of_delimiters = count_delimiters(string);
	NODE *root = (NODE*)malloc(sizeof(NODE));
	convert_string_to_tree(string,0,position_of_delimiters,root);
	free(position_of_delimiters);
	return root;
}

void test_convert_string_to_tree()
{
	char input[9][104] = {"([8,8],[4,8],[2,4],[1,2],[3,2],[6,4],[5,6],[7,6],[12,8],[10,12],[9,10],[11,10],[14,12],[13,14],[15,14])",
					     "([8,8],[4,8],[2,4],[6,4],[5,6],[7,6],[12,8],[10,12],[9,10],[11,10],[14,12],[13,14],[15,14])",
					     "([8,8],[4,8],[2,4],[1,2],[3,2],[6,4],[5,6],[7,6],[12,8],[10,12],[9,10],[11,10])",
					     "([5,5],[4,5],[2,4],[1,4],[3,5],[6,3],[7,3])",
					     "([5,5],[4,5],[3,5],[6,3],[7,3])",
					     "([5,5],[4,5],[2,4],[1,4],[3,5])",
					     "([1,1],[2,1],[3,1])",
					     "([5,5])",
					     "([1,1],[2,1])"
					    };
	char output[9][86] = {"8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$",
								  "8,4,2,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$",
								  "8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,-",
								  "5,4,2,$,1,$,3,6,$,7,$",
								  "5,4,$,3,6,$,7,$",
								  "5,4,2,$,1,$,3,$",
								  "1,2,$,3,$",
								  "5,$",
								  "1,2,$,-"
								};
	int iter_loop,index;
	for(iter_loop=0;iter_loop<9;iter_loop++)
	{
		printf("%d-->",iter_loop+1);
		if(input[iter_loop]==NULL || output[iter_loop]==NULL)
		{
			printf("INVALID INPUT");
			continue;
		}

		NODE *root1;
		root1 = driver_for_convert_string_to_tree(input[iter_loop]);
		NODE *root2 = (NODE*)malloc(sizeof(NODE));

		index = next_element_in_string(output[iter_loop],0);
		root2->data = create_number(output[iter_loop],index);
		index = next_element_in_string(output[iter_loop],index);
		construct_tree(root2,output[iter_loop],index);
		(tree_comparator(root1,root2)==1)?printf("ACCEPTED\n"):printf("REJECTED\n");
		delete_tree(root1);
		delete_tree(root2);
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	test_convert_string_to_tree();
	getchar();
	return 0;
}