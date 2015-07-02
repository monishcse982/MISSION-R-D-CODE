// S4Q5.cpp : Given a sorted linked list in ascending order (supposed to be sorted), one sub-linked list (only one part) is reversed. fix the linked list.             example: 1->2->3->5->4->6->7 (supposed to be 1->2->3->4->5->6->7) but 4->5 got reversed, fix it
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *next;
};

void delete_linked_list(NODE* head_ref)
{
	NODE *current = head_ref->next;
	NODE *next;
	while (current != NULL) 
	{
		   next = current->next;
	    free(current);
	    current = next;
	 }
		free(head_ref);
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

NODE* fix_reversed_elements_in_linked_list(NODE* input)
{
	NODE *first_reversed_node;
	if(input == NULL)
	{
		return NULL;
	}
	if(input->next == NULL)
	{
		return input;
	}
	if(input->data > input->next->data)
	{
		first_reversed_node = input->next;
		input->next = first_reversed_node->next;
		first_reversed_node->next = input;
		return first_reversed_node;
	}
	else if(input->data < input->next->data)
	{
		NODE *current_node = input, *node_after_reversed_nodes;
		while((current_node->next!=NULL) && (current_node->next->next!=NULL) && (current_node->data < current_node->next->data) && (current_node->next->data < current_node->next->next->data))
		{
			current_node = current_node->next;
		}
		if(current_node->next->next == NULL)
		{
			return input;
		}
		first_reversed_node = current_node->next;
		node_after_reversed_nodes = first_reversed_node->next->next;
		current_node->next = first_reversed_node->next;
		current_node = current_node->next;
		current_node->next = first_reversed_node;
		first_reversed_node->next = node_after_reversed_nodes;
		return input;
	}
	return input;
}

void test_fix_reversed_elements_in_linked_list()
{
	int input_array[7][20] =  {{1, 2, 3, 5, 4, 6, 7, 8, 9, 10},{2 ,1, 3, 4, 5},{1, 2, 3, 4, 6, 5},{NULL},{2,1},{1},{1,2,3,4,5,6}};
	int output_array[7][20] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},{1, 2, 3, 4, 5},{1, 2, 3, 4, 5, 6},{NULL},{1,2},{1},{1,2,3,4,5,6}};
	int iter_loop;
	for(iter_loop=0;iter_loop<7;iter_loop++)
	{
		NODE *input_list = create_linked_list(input_array[iter_loop]);
		NODE *output_list = create_linked_list(output_array[iter_loop]);
		input_list = fix_reversed_elements_in_linked_list(input_list);
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
	test_fix_reversed_elements_in_linked_list();
	getchar();
	return 0;
}