// S3Q4.cpp : Given a sorted double linked list convert that to Binary Search Tree using prev and next as left and right pointers. (find half, first half = tree , 2nd half = tree the mid element = root)
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *previous;
	NODE *next;
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

NODE* mid_element_of_DLL(NODE* input_list)
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

NODE* Sorted_DLL_to_tree(NODE *start)
{
	if(start->next == NULL)
	{
		start->previous == NULL;
		return start;
	}
	int set_previous_to_null = 0;
	if(set_previous_to_null == 0)
	{
		NODE *temp = start;
		while(temp!=NULL)
		{
			temp->previous = NULL;
			temp = temp->next;
		}
		set_previous_to_null++;
	}
	NODE *node_after_mid, *mid_node, *iter_node;
	mid_node = mid_element_of_DLL(start);
	iter_node = start;
	while(iter_node->next!=NULL && iter_node->next!=mid_node)
	{
		iter_node = iter_node->next;
	}
	iter_node->next = NULL;
	node_after_mid = mid_node->next; 
	mid_node->next = NULL;
	mid_node->previous = Sorted_DLL_to_tree(start);
	if(mid_node->previous==mid_node)
	{
		mid_node->previous=NULL;
	}
	mid_node->next = Sorted_DLL_to_tree(node_after_mid);
	if(mid_node->next==mid_node)
	{
		mid_node->next=NULL;
	}
	return mid_node;
}

void delete_linked_list(NODE *head)
{
	NODE *current = head->next;
	NODE *next;
	while (current != NULL) 
	{
		   next = current->next;
	    free(current);
	    current = next;
	 }
		free(head);
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

void print_double_linked_list(NODE *head)
{
	NODE* temp_head = head;
	while(temp_head->next!=NULL)
	{
		printf("%d->",temp_head->data);
		temp_head = temp_head->next;
	}
	printf("%d",temp_head->data);
}

NODE* create_double_linked_list(int *input)
{
	if(input == NULL)
	{
		return NULL;
	}
	int iter_loop = 0;
	NODE *head = (NODE*)malloc(sizeof(NODE));
	head->data = input[iter_loop];
	head->previous = NULL;
	head->next = NULL;
	NODE *temp_head = head;
	iter_loop++;
	while(input[iter_loop]!='\0')
	{
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		new_node->data = input[iter_loop];
		temp_head->next = new_node;
		new_node->previous = temp_head;
		temp_head = new_node;
		new_node->next = NULL;
		iter_loop++;
	}
	return head;
}

void Preorder_traversal(NODE *head)
{
	printf("%d  ",head->data);
	if(head->previous!=NULL)
	{
		Preorder_traversal(head->previous);
	}
	if(head->next!=NULL)
	{
		Preorder_traversal(head->next);
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

void test_Sorted_DLL_to_tree()
{
	int input[5][20] = {{1},{1,2,3,4},{1,2},{1,2,3},{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
	char output[5][52] = {   
					  "1,$",
					  "2,1,$,3,-,4,$",
					  "1,-,2,$",
					  "2,1,$,3,$",
					  "8,4,2,1,$,3,$,6,5,$,7,$,12,10,9,$,11,$,14,13,$,15,$"
					 };
	int iter_loop, index;
	for(iter_loop=0;iter_loop<4;iter_loop++)
	{
		printf("%d-->",iter_loop+1);
		NODE *root1 = Sorted_DLL_to_tree(create_double_linked_list(input[iter_loop]));
		NODE *root2 = (NODE*)malloc(sizeof(NODE));

		index = next_element_in_string(output[iter_loop],0);
		root2->data = create_number(output[iter_loop],index);
		index = next_element_in_string(output[iter_loop],index);
		construct_tree(root2,output[iter_loop],index);

		(tree_comparator(root1,root2) == 1)?(printf("ACCEPTED\n")):(printf("REJECTED\n"));
		delete_tree(root1);
		delete_tree(root2);
		
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_Sorted_DLL_to_tree();
	getchar();
	return 0;
}