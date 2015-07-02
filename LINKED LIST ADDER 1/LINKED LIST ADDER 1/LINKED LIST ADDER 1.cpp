// LINKED LIST ADDER 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE{
	int data;
	NODE* next;
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

NODE* reverse_the_linked_list(NODE *head, NODE *previous)
{
	if(head == NULL)
	{
		return NULL;
	}
	if(previous == NULL && head->next==NULL)
	{
		return head;
	}
	else if(previous==NULL && head->next!=NULL &&head->next->next==NULL)
	{
		head->next->next = head;
		NODE *next = head->next;
		head->next = NULL;
		head = next;
	}
	else if(previous == NULL && head->next!=NULL)
	{
		previous = head;
		NODE* temp = head->next->next;
		head = head->next;
		head->next = previous;
		previous->next = NULL;
		previous = head;
		head = temp;
		return reverse_the_linked_list(head, previous);
	}
	else if(previous!=NULL && head->next!=NULL)
	{
		NODE* temp = head->next;
		head->next = previous;
		previous = head;
		head = temp;
		return reverse_the_linked_list(head, previous);
	}
	else if(previous!=NULL && head->next == NULL)
	{
		head->next = previous;
		return head;
	}
}

int length_of_linked_list(NODE *head)
{
	int length=0;
	while (head->next!=NULL)
	{
		head = head->next;
		length++;
	}
	return length;
}

int add_data_in_linked_lists(NODE* head1, NODE* head2,int carry)
{
	int sum;
	if (head1 == NULL && head2 == NULL && carry==1)
	{
		return 2;
	}
	else if (head1 == NULL){
		head2->data += carry; 
		return 1;
	}
	else if (head2 == NULL){
		head1->data += carry;
		return 0;
	}
	sum = (head1->data + head2->data)+carry;
	head1->data = sum%10;
	head2->data = sum%10;
	if (sum/10 ==1) 
		{
			return add_data_in_linked_lists(head1->next, head2->next, 1);
	}
	else if (sum/10 ==1) 
	{
		return add_data_in_linked_lists(head1->next, head2->next, 0);
	}
}

NODE* linked_list_adder(NODE* head1, NODE* head2)
{
	int n = 0, carry = 0;
	head1 = reverse_the_linked_list(head1,NULL);
	head2 = reverse_the_linked_list(head2,NULL);
	n = add_data_in_linked_lists(head1, head2,carry);
	if (n == 1)
	{
		return reverse_the_linked_list(head2,NULL);
	}
	else if (n == 0)
		return reverse_the_linked_list(head1,NULL);
	else
	{
		head1 = reverse_the_linked_list(head1,NULL);
		NODE* CARRY_NODE = (NODE*)malloc(sizeof(NODE));
		CARRY_NODE->data = 1;
		CARRY_NODE->next = head1;
		head1 = CARRY_NODE;
		return head1;
	}
}

 void print_linked_list(NODE *head)
 {
	 while (head)
	 {
		  printf("%d",head->data);
		  head= head->next;
	
	 }
 }

 int compare_linked_lists(NODE *head1, NODE* head2)
 {
	 while(head1->next!=NULL && head2->next!=NULL)
	 {
		 if(head1->data!=head2->data)
		 {
			 return -1;
		 }
		 head1 = head1->next;
		 head2 = head2->next;
	 }
	 return 1;
 }

void test_linked_list_adder()
{
	int input_array_1[5][10]= 
	{
		{1,1,2,3,4,5,6},
		{1,2,3,4,5,6},
		{5,5,5,5},
		{4,5,6,7},
		{1,2,3,5}
	};

	int input_array_2[5][10]={
		{2,4},
		{7,5,8,9},
		{4,4,4,4,5},
		{6,7,8,9},
		{5,6}
	};

	int output_array[5][10] = 
	{
		{1,1,2,3,4,8,0},
		{1,3,1,0,4,5},
		{5,0,0,0,0},
		{1,1,3,5,6},
		{1,2,9,1}
	};
	 
	for(int iter_loop=0;iter_loop<5;iter_loop++)
	{
		NODE *head1  = create_linked_list(input_array_1[iter_loop]);
		NODE *head2  = create_linked_list(input_array_2[iter_loop]);
		head1 = linked_list_adder(head1, head2);
		(1==compare_linked_lists(head1,create_linked_list(output_array[iter_loop])))?printf("ACCEPTED\n"):printf("REJECTED\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_linked_list_adder();
	getchar();
	return 0;
}