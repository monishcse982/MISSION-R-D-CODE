// S4Q9.cpp : Given a linked list of the form 1->2->3->4->5 swap two adjacent nodes, output of the example is 2->1->4->3->5
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

NODE* reverse_in_pairs(NODE* input)
{
	if(input==NULL)
	{
		return NULL;
	}
	if(input->next == NULL)
	{
		return input;
	}
	if(input->next->next == NULL)
	{
		NODE *temp = input->next;
		temp->next = input;
		input->next = NULL;
		return temp;
	}
	NODE *slow = input,*fast = input, *head = input->next, *temp = NULL;
	while(fast->next!=NULL && fast->next->next!=NULL)
	{
		if(temp!=NULL)
		{
			temp->next = slow->next;
		}
		fast = fast->next->next;
		temp = slow;
		slow->next->next = slow;
		slow->next = fast;
		if(fast->next!=NULL && fast->next->next==NULL)
		{
			break;
		}
		slow = fast;
	}
	if(fast->next!=NULL && fast->next->next==NULL)
	{
		slow->next = fast->next;
		slow->next->next = fast;
		fast->next = NULL;
	}
	return head;
}

void test_reverse_in_pairs()
{
	int input_array[9][20] =  {{1,2,3,4,5,6},{1,2,3},{1,2},{21,36,42,58,72,35},{-1,-2,3,36,45,-10,-7},{NULL},{34,65},{-10}};
	int output_array[9][20] = {{2,1,4,3,6,5},{2,1,3},{2,1},{36,21,58,42,35,72},{-2,-1,36,3,-10,45,-7},{NULL},{65,34},{-10}};
	int iter_loop;
	for(iter_loop=0;iter_loop<8;iter_loop++)
	{
		NODE *input_list = create_linked_list(input_array[iter_loop]);
		NODE *output_list = create_linked_list(output_array[iter_loop]);
		input_list = reverse_in_pairs(input_list);
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
	test_reverse_in_pairs();
	getchar();
	return 0;
}