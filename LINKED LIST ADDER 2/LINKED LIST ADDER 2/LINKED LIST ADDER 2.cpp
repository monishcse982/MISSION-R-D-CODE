// LINKED LIST ADDER 2.cpp : Defines the entry point for the console application.
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
		NODE *new_NODE = (NODE*)malloc(sizeof(NODE));
		temp->next = new_NODE;
		temp = new_NODE;
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

NODE* linked_list_adder_2(NODE* head1, NODE* head2)
{
	NODE* head1_duplicate = head1;
	NODE* head2_duplicate = head2;
	int length_of_first_list = 0, length_of_second_list = 0;
	while (head1_duplicate != NULL)
	{
		length_of_first_list++;
		head1_duplicate = head1_duplicate->next;
	}
	while (head2_duplicate != NULL)
	{
		length_of_second_list++;
		head2_duplicate = head2_duplicate->next;
	}
	head1_duplicate = (length_of_first_list > length_of_second_list) ? head1 : head2;
	head2_duplicate = (head1_duplicate == head2) ? head1 : head2;
	NODE* TEMP = (NODE*)malloc(sizeof(NODE));
	TEMP->data = 0;
	TEMP->next = head1_duplicate;
	int dif = 0, sum = 0;
	NODE* CARRY_NODE = TEMP;
	for (dif = 0; dif<((length_of_first_list>length_of_second_list) ? (length_of_first_list - length_of_second_list) : (length_of_second_list - length_of_first_list)); dif++)
	{
		if (head1_duplicate->data != 9)
		{
			CARRY_NODE = head1_duplicate;
		}
		head1_duplicate = head1_duplicate->next;
	}
	while (head1_duplicate != NULL)
	{
		sum = head1_duplicate->data + head2_duplicate->data;
		head1_duplicate->data = sum % 10;
		if (sum < 9)
		{
			CARRY_NODE = head1_duplicate;
		}
		else
		{
			while (CARRY_NODE != head1_duplicate)
			{
				CARRY_NODE->data = (CARRY_NODE->data + 1) % 10;
				CARRY_NODE = CARRY_NODE->next;
			}
        }
		head1_duplicate = head1_duplicate->next;
		head2_duplicate = head2_duplicate->next;
    }
	head1_duplicate = (length_of_first_list > length_of_second_list) ? head1 : head2;
	if (TEMP->data == 1)
	{
		head1_duplicate = TEMP;
	}
	return head1_duplicate;
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

void test_linked_list_adder_2()
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
		head1 = linked_list_adder_2(head1, head2);
		(1==compare_linked_lists(head1,create_linked_list(output_array[iter_loop])))?printf("ACCEPTED\n"):printf("REJECTED\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_linked_list_adder_2();
	getchar();
	return 0;
}