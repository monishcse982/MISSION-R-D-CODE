// S5Q10.cpp : Given two BST's write function to check whether they are same or not, same means their structure may be different but their values are same
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *previous;
	NODE  *next;
};

void size_of_tree(NODE *root, int *size)
{
	if(root == NULL)
	{
		return;
	}
	if(root->previous!=NULL)
	{
		size_of_tree(root->previous,size);
	}
	*size = *size+1;
	if(root->next!=NULL)
	{
		size_of_tree(root->next,size);
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

void fill_inorder_of_tree_to_array(NODE *root, int *input, int *index)
{
	if(root->previous!=NULL)
	{
		fill_inorder_of_tree_to_array(root->previous,input,index);
	}
	input[*index] = root->data;
	*index = *index+1;
	if(root->next!=NULL)
	{
		fill_inorder_of_tree_to_array(root->next,input,index);
	}
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

int split_array(int* input_array, int start, int end)
{
	int high, low, pivot  = input_array[start];
	low = start;
	high = end;
	while(low<high)
	{
		while(input_array[low] <=pivot)
		{
			low++;
		}
		while(input_array[high] > pivot)
		{
			high--;
		}
		if(low<high)
		{
			input_array[low] = input_array[low] + input_array[high];
			input_array[high] = input_array[low] - input_array[high];
			input_array[low] = input_array[low] - input_array[high];
		}
	}
	input_array[start] = input_array[high];
	input_array[high] = pivot;
	return high;
}

int* Quick_Sort(int* input_array, int start, int end)
{
	int pivot;
	if(end>start)
	{
		pivot = split_array(input_array, start, end);
		Quick_Sort(input_array,start,pivot-1);
		Quick_Sort(input_array,pivot+1,end);

	}
	return input_array;
}

int check_if_trees_are_equal(NODE *root1, NODE *root2)
{
	int size = 0;
	size_of_tree(root1,&size);
	int *inorder_of_root1 = (int*)malloc((size+1)*sizeof(int));
	inorder_of_root1[size] = '\0';
	size = 0;
	size_of_tree(root2,&size);
	int *inorder_of_root2 = (int*)malloc((size+1)*sizeof(int));
	inorder_of_root2[size] = '\0';
	int index=0;
	fill_inorder_of_tree_to_array(root1,inorder_of_root1,&index);
	index=0;
	fill_inorder_of_tree_to_array(root2,inorder_of_root2,&index);
	inorder_of_root1 = Quick_Sort(inorder_of_root1,0,array_length(inorder_of_root1)-1);
	inorder_of_root2 = Quick_Sort(inorder_of_root2,0,array_length(inorder_of_root2)-1);
	for(index=0;inorder_of_root1[index]!='\0' && inorder_of_root2[index]!='\0';index++)
	{
		if(inorder_of_root1[index]!=inorder_of_root2[index])
		{
			free(inorder_of_root1);
			free(inorder_of_root2);
			return 0;
		}
	}
	free(inorder_of_root1);
	free(inorder_of_root2);
	return 1;
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

void Inorder(NODE *root)
{
	if(root->previous!=NULL)
	{
		Inorder(root->previous);
	}

	printf("%d ",root->data);

	if(root->next!=NULL)
	{
		Inorder(root->next);
	}
}

void test_check_if_trees_are_equal()
{
	char input_tree1[5][52] = {"8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$","1,2,$,3,$","2,1,$,3,-,4,$","4,3,1,$,2,$,5,6,$,7,$"};
	char input_tree2[5][52] = {"1,2,4,8,$,9,$,5,10,$,11,$,3,6,12,$,13,$,7,14,$,15,$","3,1,$,2,$","3,2,-,1,$,4,$","4,3,2,-,1,$,-,5,-,6,-,7,$,-"};
	int iter_loop;
	for(iter_loop=0;iter_loop<4;iter_loop++)
	{
		int index=0;
		NODE *root1 = (NODE*)malloc(sizeof(NODE));
		index = next_element_in_string(input_tree1[iter_loop],0);
		root1->data = create_number(input_tree1[iter_loop],index);
		index = next_element_in_string(input_tree1[iter_loop],index);
		construct_tree(root1,input_tree1[iter_loop],index);

		NODE *root2 = (NODE*)malloc(sizeof(NODE));
		index = next_element_in_string(input_tree2[iter_loop],0);
		root2->data = create_number(input_tree2[iter_loop],index);
		index = next_element_in_string(input_tree2[iter_loop],index);
		construct_tree(root2,input_tree2[iter_loop],index);

		(1==check_if_trees_are_equal(root1,root2))?printf("ACCEPTED\n"):printf("REJECTED\n");

		delete_tree(root1);
		delete_tree(root2);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_check_if_trees_are_equal();
	getchar();
	return 0;
}