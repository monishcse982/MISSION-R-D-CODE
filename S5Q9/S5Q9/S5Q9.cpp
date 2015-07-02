// S5Q9.cpp : Given a single sorted linked list, create a binary search tree from that. tree memory should be allocated
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *next;
};

struct TREE_NODE
{
	int data;
	TREE_NODE *previous;
	TREE_NODE *next; 
};

int tree_comparator(TREE_NODE *root1, TREE_NODE *root2)
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
		root->previous = NULL;
		root->next = NULL;
		return index;
	}
	int result;
	result = create_number(input_string,index);
	if(result!=NULL)
	{
		TREE_NODE *temp = (TREE_NODE*)malloc(sizeof(TREE_NODE));
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
		TREE_NODE *temp = (TREE_NODE*)malloc(sizeof(TREE_NODE));
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

int array_length(int *input_array)
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

NODE* mid_element_of_list(NODE* input_list)
{
	NODE *slow, *fast;
	slow = fast = input_list;
	while(fast->next!=NULL && fast->next->next!=NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

void delete_tree(TREE_NODE *root)
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

TREE_NODE* LINKED_LIST_TO_TREE(NODE *start,TREE_NODE *root)
{
	if(start->next==NULL)
	{
		TREE_NODE *new_node = (TREE_NODE*)malloc(sizeof(TREE_NODE));
		new_node->data = start->data;
		new_node->previous = new_node->next = NULL;
		free(start);
		return new_node;
	}
	NODE *node_after_mid, *mid_node, *iter_node;
	TREE_NODE *new_node = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	mid_node= mid_element_of_list(start);
	iter_node = start;
	new_node->data = mid_node->data;
	root = new_node;
	node_after_mid = mid_node->next; 
	while(iter_node->next!=NULL && iter_node->next!=mid_node)
	{
		if(iter_node == mid_node)
		{
			break;
		}
		iter_node = iter_node->next;
	}
	iter_node->next = NULL;
	root->next = NULL;
	root->previous = LINKED_LIST_TO_TREE(start,root);
	if(root->previous->data == root->data)
	{
		free(root->previous);
		root->previous=NULL;
	}
	root->next = LINKED_LIST_TO_TREE(node_after_mid,root);
	if(root->next->data == root->data)
	{
		free(root->next);
		root->next=NULL;
	}
	if(!mid_node)
	{
		free(mid_node);
	}
	return root;
}

NODE* create_linked_list(int *input_array)
{
	int iter_loop=0;
	NODE *head = (NODE *)malloc(sizeof(NODE));
	NODE *temp = head;
	head->data = input_array[iter_loop];
	temp->next=NULL;
	iter_loop++;
	while(input_array[iter_loop]!='\0')
	{
		NODE *new_node = (NODE *)malloc(sizeof(NODE));
		temp->next = new_node;
		temp = new_node;
		temp->data = input_array[iter_loop];
		temp->next=NULL;
		iter_loop++;
	}
	return head;
}

TREE_NODE* LINKED_LIST_TO_TREE_INVOKER(int *input_array)
{
	NODE *head = create_linked_list(input_array);
	TREE_NODE *root = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	root = LINKED_LIST_TO_TREE(head,root);
	return root;
}

void test_LINKED_LIST_TO_TREE()
{
	int input[9][21] = {{1},{1,2},{1,2,3},{1,2,3,4,5},{1,2,3,4,5,6,7},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9,10,11},{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},												{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}};

	char expected_output[9][77] = {"1,$",
								   "1,-,2,$",
								   "2,1,$,3,$",
									"3,1,-,2,$,4,-,5,$",
								   "4,2,1,$,3,$,6,5,$,7,$",
								   "5,2,1,$,3,-,4,$,7,6,$,8,-,9,$",
								   "6,3,1,-,2,$,4,-,5,$,9,7,-,8,$,10,-,11,$",
								   "8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$",
								   "10,5,2,1,$,3,-,4,$,7,6,$,8,-,9,$,15,12,11,$,13,-,14,$,18,16,-,17,$,19,-,20,$"
								  };
	int iter_loop;
	for(iter_loop=0;iter_loop<9;iter_loop++)
	{
		printf("%d-->",iter_loop+1);
		int index;
		TREE_NODE *root1 = (TREE_NODE*)malloc(sizeof(TREE_NODE));
		root1 = LINKED_LIST_TO_TREE_INVOKER(input[iter_loop]);

		TREE_NODE *root2 = (TREE_NODE*)malloc(sizeof(TREE_NODE));
		index = next_element_in_string(expected_output[iter_loop],0);
		root2->data = create_number(expected_output[iter_loop],index);
		index = next_element_in_string(expected_output[iter_loop],index);
		construct_tree(root2,expected_output[iter_loop],index);

		(1==tree_comparator(root1,root2))?printf("ACCEPTED\n"):printf("REJECTED\n");
		delete_tree(root1);
		delete_tree(root2);
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	test_LINKED_LIST_TO_TREE();
	getchar();
	return 0;
}