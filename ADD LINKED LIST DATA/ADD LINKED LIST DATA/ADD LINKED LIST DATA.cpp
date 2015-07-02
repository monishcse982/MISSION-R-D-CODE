// ADD LINKED NODE DATA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE* next;
};

NODE* reverse_linked_list(NODE *head)
{
	NODE *previous_list=head, *current=head, *temp=head;
	current = previous_list->next;
	temp = current;
	previous_list->next =NULL;
	while(current->next!=NULL)
	{
		if(current->next==NULL)
		{
			current->next = previous_list;
		}
		current = current->next;
		temp->next = previous_list;
		previous_list  = temp;
		temp = current;
	}
	return current;
}

NODE* create_linked_NODE(char *input)
{
	int iter_loop=0, num;
	NODE *head = (NODE*)malloc(sizeof(NODE));
	NODE *temp = head;
	if(input[iter_loop]>='0' && input[iter_loop]<='9')
		{
			num = input[iter_loop] & ('p'-'a');
			head->data = num;
			head->next=NULL;
		}
		else if(!(input[iter_loop]>='0' && input[iter_loop]<='9'))
		{
			printf("INVALID INPUT\n");
			return NULL;
		} 
	while(input[iter_loop]!='\0')
	{
		if(input[iter_loop]>='0' && input[iter_loop]<='9')
		{
			num = input[iter_loop] & ('p'-'a');
			NODE *new_node = (NODE*)malloc(sizeof(NODE));
			new_node->data = num;
			new_node->next = NULL;
			temp->next = new_node;
			temp = new_node;
			iter_loop++;
		}
		else if(!(input[iter_loop]>='0' && input[iter_loop]<='9'))
		{
			printf("INVALID INPUT\n");
			return NULL;
		} 
	}
	return head;
}

NODE* add_linked_lists(NODE* head1, NODE* head2, int *carry, NODE *result_head)
{
	if(head1->next==NULL && head2->next!=NULL)
	{
		NODE *temp_head = head2;
	}
	else if(head2->next==NULL && head1->next!=NULL)
	{
		NODE *temp_head = head1;
	}
	if(head1->next!=NULL && head2->next!=NULL)
	{
		result_head
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}