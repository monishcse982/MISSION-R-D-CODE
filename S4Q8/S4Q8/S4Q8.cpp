// S4Q8.cpp : given an unsorted linked list, and a value, remove all the nodes that contain value greater than the value given as input
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

NODE* remove_all_nodes_greater_than_key(NODE *input,int key)
{
	NODE *head=input;
	if(input==NULL)
	{
		return NULL;
	}
	if(key == NULL)
	{
		return input;
	}
	NODE* temp = input;
	if(input->data > key)
	{
		while(input->next!=NULL && input->next->data > key)
		{
			input = input->next;
		}

		NODE* next = input->next;
		input->next = NULL;
		delete_linked_list(temp);
		input = next;
		if(input->data > key)
		{
			free(input);
			return NULL;
		}
		if(input==NULL)
		{
			return NULL;
		}
		head = input;
	}
	while(input!=NULL)
	{
		NODE *temp = input;
		while(input->next!=NULL && input->next->data > key)
		{
			input = input->next;
		}
		if(input->data > key)
		{
			NODE *list_to_be_deleted = temp->next;
			temp->next = input->next;
			input->next = NULL;
			input = temp->next;
			delete_linked_list(list_to_be_deleted);
		}
		else if(input->data <= key)
		{
			input = input->next;
		}
	}
	return head;
}

void test_remove_all_nodes_greater_than_key()
{
	int input_array[5][20] = {{12,58,93,58,96,36,217,47,36,27,63},{-1,6,20,-25,32,45},{-90,-100,-98,-1,-56,-63,132,167,189}};
	int output_array[5][20] = {{12,36,36,27},{-25},{-90,-100,-98,-1,-56,-63}};
	int key_values[5] = {36,-25,50};
	int iter_loop;
	for(iter_loop=0;iter_loop<3;iter_loop++)
	{
		NODE *input_list, *output_list;
		input_list = create_linked_list(input_array[iter_loop]);
		output_list = create_linked_list(output_array[iter_loop]);
		input_list = remove_all_nodes_greater_than_key(input_list,key_values[iter_loop]);
		NODE *head_input_list = input_list;
		NODE *head_output_list = output_list;
		if(input_list == NULL && output_list == NULL)
		{
			printf("ACCEPTED\n");
			delete_linked_list(head_input_list);
			delete_linked_list(head_output_list);
		}
		while(input_list!=NULL || output_list!=NULL)
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
		if(input_list==NULL && output_list==NULL)
		{
				printf("ACCEPTED\n");
				delete_linked_list(head_input_list);
				delete_linked_list(head_output_list);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_remove_all_nodes_greater_than_key();
	getchar();
	return 0;
}