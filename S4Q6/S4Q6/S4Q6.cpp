// S4Q6.cpp : Given a single sorted circular linked list (where last element connects to first element and head is at least element of the list), a value, insert the vlaue in the linked list
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *next;
};

void delete_circular_linked_list(NODE *head)
{
	NODE *temp, *next;
	next = head->next;
	while(next!=head)
	{
		temp = next->next;
		free(next);
		next = temp;
	}
	free(head);
}

NODE* create_circular_linked_list(int *input_array)
{
	int iter_loop=0;
	NODE *head = (NODE*)malloc(sizeof(NODE));
	NODE *temp = head;
	head->data = input_array[iter_loop];
	temp->next=temp;
	iter_loop++;
	while(input_array[iter_loop]!='\0')
	{
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		temp->next = new_node;
		temp = new_node;
		temp->data = input_array[iter_loop];
		temp->next=head;
		iter_loop++;
	}
	return head;
}

NODE* print_circular_linked_list(NODE* input)
{
	printf("LIST DATA:\n");
	NODE* temp = input;
	while(temp->next!=input)
	{
		printf("%d->",temp->data);
		temp = temp->next;
	}
	printf("%d\n",temp->data);
	return input;
}

NODE* insert_into_circular_linked_list(NODE *input_list, int key)
{
	NODE *head = input_list;
	if(key < input_list->data)
	{
		while(input_list->next!=head)
		{
			input_list = input_list->next;
		}
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		new_node->data = key;
		new_node->next = input_list->next;
		input_list->next = new_node;
		return new_node;
	}

	while(input_list->next!=head && input_list->next->data<key)
	{
		input_list = input_list->next;
	}
	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = key;
	new_node->next = input_list->next;
	input_list->next = new_node;
	return head;
}

void test_insert_into_circular_linked_list()
{
	int input_array[8][20] = {{1,2,4,5,6,7,8,9,10},{2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9},{12,34,56,78,90},{NULL},{1,2},{1,2},{-98,-85,-77,-62,-56}};
	int output_array[8][20] = {{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9,10},{12,34,46,56,78,90},{NULL},{1,2,3},{-1,1,2},{-98,-85,-77,-62,-56,54}};
	int key_values[9] = {3,1,10,46,NULL,3,-1,54};
	int iter_loop;
	for(iter_loop=0;iter_loop<8;iter_loop++)
	{
		NODE *input_list = create_circular_linked_list(input_array[iter_loop]);
		NODE *output_list = create_circular_linked_list(output_array[iter_loop]);
		input_list = insert_into_circular_linked_list(input_list,key_values[iter_loop]);
		NODE *input_head = input_list;
		NODE *output_head = output_list;
		if(input_list == NULL && output_list == NULL)
		{
			printf("ACCEPTED\n");
			break;
		}
		while (input_list!=input_head)
		{
			if(input_list->data != output_list->data)
			{
				printf("REJECTED\n");
				delete_circular_linked_list(input_list);
				delete_circular_linked_list(output_list);
				break;
			}
			input_list = input_list->next;
			output_list = output_list->next;
		}
		if(input_list == input_head && output_list == output_head)
		{
			printf("ACCEPTED\n");
			delete_circular_linked_list(input_list);
			delete_circular_linked_list(output_list);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_insert_into_circular_linked_list();
	getchar();
	return 0;
}