// S4Q10.cpp : Given a linked list and value K, keep first K elemetns and remove next K elements, keep again K elements and remove next K elements.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *next;
};

void delete_linked_list(NODE *head)
{
	NODE *temp, *next;
	next = head->next;
	while(next)
	{
		temp = next->next;
		free(next);
		next = temp;
	}
	free(head);
}

NODE* create_linked_list(int *input_array)
{
	int iter_loop=0;
	NODE *head = (NODE*)malloc(sizeof(NODE));
	NODE *temp = head;
	head->data = input_array[iter_loop];
	temp->next=NULL;
	iter_loop++;
	while(input_array[iter_loop]!='\0')
	{
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		temp->next = new_node;
		temp = new_node;
		temp->data = input_array[iter_loop];
		temp->next=NULL;
		iter_loop++;
	}
	return head;
}

NODE* print_linked_list(NODE* input)
{
	printf("LIST DATA:\n");
	NODE* temp = input;
	while(temp->next!=NULL)
	{
		printf("%d->",temp->data);
		temp = temp->next;
	}
	printf("%d\n",temp->data);
	return input;
}

NODE* keep_k_delete_k(NODE* input, int k)
{
	if(k<0)
	{
		return input;
	}
	if(k==0)
	{
		return input;
	}
	if(input==NULL || k==NULL)
	{
		return NULL;
	}
	NODE *head = input;
	int iter_loop, delete_flag=0;
	NODE *k_node =NULL;
	for(iter_loop=0;input!=NULL;iter_loop++)
	{
		if((iter_loop+1)%k == 0)
		{
			if(delete_flag==0)
			{
				k_node = input;
				delete_flag++;
				input = input->next;
			}
			else if(delete_flag==1)
			{
				NODE *first_element_to_delete = k_node->next;
				k_node->next = input->next;
				input->next =NULL;
				input = k_node->next;
				delete_linked_list(first_element_to_delete);
				delete_flag--;
			}
		}
		else if((iter_loop+1)%k != 0)
		{
			input = input->next;
		}
	}
	return head;
}

void test_keep_k_delete_k()
{
	
	int input_array[9][10]  = {{9, 8, 7, 6, 5, 4, 3, 2, 1},{34, 76, 23, 98, 43},{8, 7, 6, 5, 4, 3, 2, 1},{3,2,1},{236,235,440,100},{9, 8, 7, 6, 5, 4, 3, 2, 1},{8, 7, 6, 5, 4, 3, 2, 1},{8, 7, 6, 5, 4, 3, 2, 1}};
	int output_array[9][10] = {{9, 8, 7, 3, 2, 1},{34, 76, 43},{8, 6, 4, 2},{3, 2, 1},{236, 235},{9, 8, 7, 6, 5, 4, 3, 2, 1},{8, 7, 6, 5},{8, 7, 6, 5, 4, 3, 2, 1}};
	int k_values[8] = {3,2,1,0,2,9,4,-6};
	int iter_loop;
	for(iter_loop=0;iter_loop<8;iter_loop++)
	{
		NODE *input_list = create_linked_list(input_array[iter_loop]);
		NODE *output_list = create_linked_list(output_array[iter_loop]);
		input_list = keep_k_delete_k(input_list,k_values[iter_loop]);
		NODE *head_input_list = input_list;
		NODE *head_output_list = output_list;
		if(input_list == NULL && output_list == NULL)
		{
			printf("ACCEPTED\n");
			break;
		}
		while (input_list!=NULL || output_list!=NULL)
		{
			if(input_list->data != output_list->data)
			{
				printf("REJECTED\n");
				delete_linked_list(head_input_list);
				delete_linked_list(head_output_list);
				break;
			}
			input_list = input_list->next;
			output_list = output_list->next;
		}
		if(input_list == NULL && output_list == NULL)
		{
			printf("ACCEPTED\n");
			delete_linked_list(head_input_list);
			delete_linked_list(head_output_list);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_keep_k_delete_k();
	getchar();
	return 0;
}