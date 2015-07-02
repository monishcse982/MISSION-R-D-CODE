// S5Q5.cpp : Given a binary search tree, where two node values are swapped. fix those two values
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
	else if((root1->left!=NULL && root2->left==NULL) || (root1->left==NULL && root2->left!=NULL))
	{
		return -1;
	}
	else if((root1->right!=NULL && root2->right==NULL) || (root1->right==NULL && root2->right!=NULL))
	{
		return -1;
	}

	if(root1->left!=NULL && root2->left!=NULL)
	{
		int result = tree_comparator(root1->left,root2->left);
		if(result==-1)
		{
			return -1;
		}
	}

	if(root1->right!=NULL && root2->right!=NULL) 
	{
		int result = tree_comparator(root1->right,root2->right); 
		if(result==-1)
		{
			return -1;
		}
	}
	return 1;
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

int size_of_tree(NODE *root, int size)
{
	if(root->left!=NULL)
	{
		size = size_of_tree(root->left,size);
	}

	size++;

	if(root->right!=NULL)
	{
		size = size_of_tree(root->right,size);
	}
	return size;
}

int Inorder_traversal(NODE *root, int index, int *traversal_array)
{
	if(root->left!=NULL)
	{
		index = Inorder_traversal(root->left,index, traversal_array);
	}

	traversal_array[index] = root->data;
	index++;

	if(root->right!=NULL)
	{
		index = Inorder_traversal(root->right,index, traversal_array);
	}
	return index;
}

void print_inorder(NODE *root)
{
	if(root->left!=NULL)
	{
		print_inorder(root->left);
	}
	printf("%d ",root->data);
	if(root->right!=NULL)
	{
		print_inorder(root->right);
	}
}

NODE* find_node_in_a_tree(NODE* root,int key)
{
	if(root->data == key)
	{
		return root;
	}

	if(root->left!=NULL)
	{
		NODE *temp = find_node_in_a_tree(root->left,key);
		if(temp->data == key)
		{
			return temp;
		}
	}
	if(root->right!=NULL)
	{
		NODE *temp = find_node_in_a_tree(root->right,key);
		if(temp->data == key)
		{
			return temp;
		}
	}
}

NODE* swap_nodes(NODE *root)
{
	int size = size_of_tree(root,0);
	int *traversal_array = (int*)malloc((size+1)*sizeof(int));
	traversal_array[size] ='\0';
	Inorder_traversal(root,0,traversal_array);
	int swap_node1_value=-1,swap_node2_value=-1,index=0;
	for(int iter_loop=0;traversal_array[iter_loop]!='\0';iter_loop++)
	{
		if(iter_loop==0 && traversal_array[iter_loop]>traversal_array[iter_loop+1])
		{
			if(index==0)
			{
				swap_node1_value = traversal_array[iter_loop];
				index++;
			}
		}

		else if(traversal_array[iter_loop+1]=='\0' &&  traversal_array[iter_loop]<traversal_array[iter_loop-1])
		{
			swap_node2_value = traversal_array[iter_loop];
			break;
		}

		else if((traversal_array[iter_loop]>traversal_array[iter_loop-1]) && (traversal_array[iter_loop]<traversal_array[iter_loop+1]))
		{
			continue;
		}
		else if(!((traversal_array[iter_loop]>traversal_array[iter_loop-1]) && (traversal_array[iter_loop]<traversal_array[iter_loop+1])))
		{
			if(traversal_array[iter_loop-1]<traversal_array[iter_loop+1])
			{
				if(index==0)
				{
					swap_node1_value = traversal_array[iter_loop];
					index++;
				}
				else if(index==1)
				{
					swap_node2_value = traversal_array[iter_loop];
					break;
				}
			}
			if(traversal_array[iter_loop-1]>traversal_array[iter_loop+1])
			{
				if(traversal_array[iter_loop]<traversal_array[iter_loop-1])
				{
					continue;
				}
				else if(traversal_array[iter_loop]>traversal_array[iter_loop+1])
				{
					if(index==0)
					{
						swap_node1_value = traversal_array[iter_loop+1];
						index++;
					}
					else if(index==1)
					{
						swap_node2_value = traversal_array[iter_loop+1];
						break;
					}

				}
			}
		}
	}

	if(swap_node1_value * swap_node2_value<=0)
	{
		return root;
	}
	NODE *first_swap_node=NULL, *second_swap_node=NULL;

	if(root->data!=swap_node1_value && root->data!=swap_node2_value)
	{
		first_swap_node = find_node_in_a_tree(root,swap_node1_value);
		second_swap_node = find_node_in_a_tree(root,swap_node2_value);
	}
	else if(root->data == swap_node1_value && root->data != swap_node2_value)
	{
		first_swap_node = root;
		second_swap_node = find_node_in_a_tree(root,swap_node2_value);
	}
	else if(root->data != swap_node1_value && root->data == swap_node2_value)
	{

		second_swap_node = root;
		first_swap_node = find_node_in_a_tree(root,swap_node1_value);
	}
	first_swap_node->data = first_swap_node->data + second_swap_node->data;
	second_swap_node->data = first_swap_node->data-second_swap_node->data;
	first_swap_node->data = first_swap_node->data-second_swap_node->data;
	free(traversal_array);
	return root;
}

void test_swap_nodes()
{
	char expected_output[4][63] = { "8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$", "6,3,2,1,$,-,5,4,$,-,9,8,7,$,-,11,10,$","5,2,1,$,3,-,4,$,7,6,$,8,-,9,$"};
	char input[4][3][63] = {
		{"1,4,2,8,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$","8,4,2,1,$,3,$,6,5,$,15,$,12,10,9,$,11,$,14,13,$,7,$","8,4,1,2,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$"},		{ "10,3,2,1,$,-,5,4,$,-,9,8,7,$,-,11,6,$", "6,3,1,2,$,-,5,4,$,-,9,8,7,$,-,11,10,$", "6,3,2,7,$,-,5,4,$,-,9,8,1,$,-,11,10,$"},
		{"9,2,1,$,3,-,4,$,7,6,$,8,-,5,$","5,2,1,$,3,-,4,$,6,7,$,8,-,9,$","5,8,1,$,3,-,4,$,7,6,$,2,-,9,$"},
						  };
	int iter_loop,iter_loop2;

	for(iter_loop=0;iter_loop<3;iter_loop++)
	{
		int index;
		NODE *input_root = (NODE*)malloc(sizeof(NODE));
			index = next_element_in_string(expected_output[iter_loop],0);
			input_root->data = create_number(expected_output[iter_loop],index);
			index = next_element_in_string(expected_output[iter_loop],index);
			construct_tree(input_root,expected_output[iter_loop],index);
		for(iter_loop2=0;iter_loop2<3;iter_loop2++)
		{
			int index;
			NODE *output_root = (NODE*)malloc(sizeof(NODE));
			index = next_element_in_string(input[iter_loop][iter_loop2],0);
			output_root->data = create_number(input[iter_loop][iter_loop2],index);
			index = next_element_in_string(input[iter_loop][iter_loop2],index);
			construct_tree(output_root,input[iter_loop][iter_loop2],index);
			output_root = swap_nodes(output_root);
			(tree_comparator(input_root,output_root)==1)?printf("ACCEPTED\n"):printf("REJECTED\n");
		}
		delete_tree(input_root);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_swap_nodes();
	getchar();
	return 0;
}