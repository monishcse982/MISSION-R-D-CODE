// S4Q7.cpp : Given a single sorted (ascending) linked list, find the median of the linked list
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

float median_of_a_linked_list(NODE* head)
{
	
	if(head->next == NULL)
	{
		return (float)head->data;
	}
	if(head->next->next == NULL)
	{
		return (float)((head->data+head->next->data)/2);
	}
	NODE *slow = head, *fast = head;
	while(fast->next!=NULL && fast->next->next!=NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	if(fast->next!=NULL)
	{
		return (float)((slow->data+slow->next->data)/2);
	}
	return (float)slow->data;
}

void test_median_of_a_linked_list()
{
	int input_array[9][12]  = {{1,2,3,4,5,6,7,8,9},
			{23, 34, 43, 76, 98},
			{2,1},
			{1},
			{NULL},
			{1,2,3,4,5,6,7,8},
			{1,2,3}
			,{100, 235, 236, 440},
			{20,25,32,46,57,69,71,83,92,101,108}};
	float output_array[9] = {5.0,43.0,1.0,1.0,NULL,4.0,2.0,235.0,69.0};
	int iter_loop;
	for(iter_loop=0;iter_loop<9;iter_loop++)
	{
		NODE *input_list;
		input_list = create_linked_list(input_array[iter_loop]);
		float result = median_of_a_linked_list(input_list);
		NODE *list_head = input_list;
		if(result == NULL && output_array[iter_loop])
		{
			printf("ACCEPTED\n");
			delete_linked_list(list_head);
		}
		else if(result == output_array[iter_loop])
		{
			printf("ACCEPTED\n");
			delete_linked_list(list_head);
		}
		else if(result!=output_array[iter_loop])
		{
			printf("REJECTED\n");
			delete_linked_list(list_head);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_median_of_a_linked_list();
	getchar();
	return 0;
}