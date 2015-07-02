// S3Q7.cpp : Compute weight of all nodes in a tree.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *left_child;
	NODE *right_child;
};

int next_element_in_string(char *input, int index)
{
	if(input[0]==NULL)
	{
		printf("NULL\n");
		return NULL;
	}
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
	if(input_string[0]== NULL)
	{
		printf("NULL\n");
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

void Preorder_traversal(NODE *root)
{
	printf("%d,",root->data);

	if(root->left_child!=NULL)
	{
		Preorder_traversal(root->left_child);
	}

	if(root->right_child!=NULL)
	{
		Preorder_traversal(root->right_child);
	}

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

void compute_weights(NODE *root)
{
	if(root == NULL)
	{
		return;
	}
	if(root->left_child!=NULL)
	{
		compute_weights(root->left_child);
	}

	if(root->right_child!=NULL)
	{
		compute_weights(root->right_child);
	}
	if(root->left_child == NULL && root->right_child == NULL)
	{
		root->data = 1;
	}
	else if(root->left_child!=NULL && root->right_child!=NULL)
	{
		root->data = root->left_child->data + root->right_child->data + 1;
	}
	else if(root->left_child==NULL && root->right_child!=NULL)
	{
		root->data = root->right_child->data+1;
	}
	else if(root->left_child!=NULL && root->right_child==NULL)
	{
		root->data = root->left_child->data+1;
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

void test_compute_weights()
{
	char input[13][52] = {"16,20,40,16,$,-,90,$,34,18,-,41,$,12,$",
						 "1,2,4,8,$,9,$,5,10,$,11,$,3,6,12,$,13,$,7,14,$,15,$",
						 "25,76,42,$,23,$,98,24,12,-,-,-",
						 "86,94,22,6,$,-,89,-,2,$",
						 "60,100,91,$,26,$,250,35,$,42,24,-,86,$,-",
						  "5,$",
						  "1,2,$,3,$",
						  "45,67,$,-",
						  "1,$",
						 "2,1,$,3,-,4,$",
						 "1,-,2,$",
						 "2,1,$,3,$",
						 "8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$"};

	char output[13][47] = {"9,4,2,1,$,-,1,$,4,2,-,1,$,1,$",
						  "15,7,3,1,$,1,$,3,1,$,1,$,7,3,1,$,1,$,3,1,$,1,$",
						  "7,3,1,$,1,$,3,2,1,-,-,-",
						  "6,5,2,1,$,-,2,-,1,$",
						  "9,3,1,$,1,$,5,1,$,3,2,-,1,$,-",
						  "1,$",
						  "3,1,$,1,$",
						  "2,1,$,-",
						  "1,$",
						  "4,1,$,2,-,1,$",
						  "2,-,1,$",
						  "3,1,$,1,$",
						  "15,7,3,1,$,1,$,3,1,$,1,$,7,3,1,$,1,$,3,1,$,1,$"};
	int index,iter_loop;

	for(iter_loop=0;iter_loop<13;iter_loop++)
	{
		printf("%d-->",iter_loop+1);
		NODE *root = (NODE*)malloc(sizeof(NODE));
		NODE *root2 = (NODE*)malloc(sizeof(NODE));

		index = next_element_in_string(input[iter_loop],0);
		root->data = create_number(input[iter_loop],index);
		index = next_element_in_string(input[iter_loop],index);
		construct_tree(root,input[iter_loop],index);

		index = next_element_in_string(output[iter_loop],0);
		root2->data = create_number(output[iter_loop],index);
		index = next_element_in_string(output[iter_loop],index);
		construct_tree(root2,output[iter_loop],index);

		compute_weights(root);

		(tree_comparator(root,root2) == 1)?(printf("ACCEPTED\n")):(printf("REJECTED\n"));
		delete_tree(root);
		delete_tree(root2);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_compute_weights();
	getchar();
	return 0;
}