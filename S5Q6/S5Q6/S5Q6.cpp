// S5Q6.cpp : Defines the entry point for the console application.
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

int array_length(int *input_array)
{
	int iter_loop=0;

	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
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

int string_length(char* input_array)
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

NODE* construct_tree_from_inorder_preorder(int *inorder, int *preorder, int inorder_start_index, int inorder_end_index, int *preorder_index)
{
	if(inorder_start_index > inorder_end_index)
	{
		return NULL;
	}
	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = preorder[*preorder_index];
	*preorder_index = *preorder_index+1;
	if(inorder_start_index == inorder_end_index)
	{
		new_node->previous = new_node->next = NULL;
		return new_node;
	}
	int iter_loop=inorder_start_index, inorder_index=0;
	while(iter_loop<=inorder_end_index)
	{
		if(new_node->data == inorder[iter_loop])
		{
			inorder_index = iter_loop;
			break;
		}
		iter_loop++;
	}
	new_node->previous = construct_tree_from_inorder_preorder(inorder, preorder, inorder_start_index, inorder_index-1,preorder_index);
	new_node->next = construct_tree_from_inorder_preorder(inorder, preorder, inorder_index+1, inorder_end_index,preorder_index);
	return new_node;
}

void test_tree_construction()
{
	char inorder[5][36] = { "8,4,9,2,10,5,11,1,12,6,13,3,14,7,15",
							"1,2,3,4",
							"1,2,3",
							"1,2,3,4,5,6,7,8,9,10,11,12,13,14,15",
							"1,2"
							};

	char preorder[5][36] = { "1,2,4,8,9,5,10,11,3,6,12,13,7,14,15",
							 "2,1,3,4",
							 "2,1,3",
							 "8,4,2,1,3,6,5,7,12,10,9,11,14,13,15",
							 "1,2"
						   };

	char expected_tree[5][52] = {"1,2,4,8,$,9,$,5,10,$,11,$,3,6,12,$,13,$,7,14,$,15,$",
		   						 "2,1,$,3,-,4,$",
								 "2,1,$,3,$",
								 "8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$",
								 "1,-,2,$"
								};
	int iter_loop;
	for(iter_loop=0;iter_loop<5;iter_loop++)
	{
		printf("%d-->",iter_loop+1);
		int preorder_index = 0;
		int *inorder_array = string_to_array(inorder[iter_loop]);
		int *preorder_array = string_to_array(preorder[iter_loop]);
		NODE *head  = construct_tree_from_inorder_preorder(inorder_array,preorder_array,0,array_length(inorder_array)-1,&preorder_index);
		NODE *root = (NODE*)malloc(sizeof(NODE));
		int index;
		index = next_element_in_string(expected_tree[iter_loop],0);
		root->data = create_number(expected_tree[iter_loop],index);
		index = next_element_in_string(expected_tree[iter_loop],index);
		construct_tree(root,expected_tree[iter_loop],index);
		(1==tree_comparator(head,root))?printf("ACCEPTED\n"):printf("REJECTED\n");
		delete_tree(head);
		free(inorder_array);
		free(preorder_array);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_tree_construction();
	getchar();
	return 0;
}