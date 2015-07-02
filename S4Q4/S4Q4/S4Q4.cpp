// S4Q4.cpp : Given two sorted linked lists, write a function to merge the two linked lists to one sorted linked list
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
	if(input_array == NULL)
	{
		return NULL;
	}
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

NODE* merge_sorted_linked_lists(NODE *list1, NODE *list2)
{
	if(list1->next == NULL && list2->next == NULL)
	{
		if(list1->data < list2->data)
		{
			list1->next = list2;
		}
		else if(list1->data > list2->data)
		{
			list2->next = list1;
		}
		return NULL;
	}
	NODE *return_head = list2;
	if(list2->next == NULL)
	{
		if(list1->data < list2->data)
		{
			list1->next = list2;
			return_head = list1;
			return return_head;
		}
		else if(list1->data > list2->data)
		{
			list2->next = list1;
			return return_head;
		}
	}
	while(list1!=NULL)
	{
		NODE *temp_list1 = list1->next;
		if(list1->data <= list2->data)
		{
			list1->next = list2;
			list2 = list1;
		}
		else if(list1->data > list2->data)
		{
			while((list2->next!=NULL) && (list2->next->data < list1->data))
			{
				list2 = list2->next;
			}
			if(list2->next!=NULL)
			{
				list1->next = list2->next;
				list2->next = list1;
				list2 = list1;
			}
			else if(list2->next==NULL)
			{
				list2->next = list1;
				list1->next = NULL;
			}
		}
		list1 = temp_list1;
	}
}

void test_merging_sorted_linked_lists()
{
	int input_array_1[5][18] = {{11,17,25,36,41,55,65,77,83,92,97},{1},{NULL},{10,13,22,91,99},{2}}; 
	int input_array_2[5][18] = {{10,13,22,91,99},{2},{NULL},{11,17,25,36,41,55,65,77,83,92,97},{1}};
	int output_array[5][18] = {{10,11,13,17,22,25,36,41,55,65,77,83,91,92,97,99},{1,2},{NULL},{10,11,13,17,22,25,36,41,55,65,77,83,91,92,97,99},{1,2}};
	int iter_loop;
	for(iter_loop=0;iter_loop<5;iter_loop++)
	{
		NODE *input_list1 = create_linked_list(input_array_1[iter_loop]);
		NODE *input_list2 = create_linked_list(input_array_2[iter_loop]);
		NODE *output_list = create_linked_list(output_array[iter_loop]);
		NODE *temp;
		if(input_array_1[iter_loop][0]<input_array_2[iter_loop][0])
		{
			temp = input_list1;
		}
		else if(input_array_1[0]>input_array_2[0])
		{
			temp = input_list2;
		}
		merge_sorted_linked_lists(input_list1,input_list2);
		input_list2 = temp;
		NODE *head_input_list2 = input_list2;
		NODE *head_output_list = output_list;
		if(input_list2 ==NULL && output_list ==NULL)
		{
			printf("ACCEPTED\n");
		}
		while(input_list2!=NULL || output_list!=NULL)
		{
			if(input_list2->data != output_list->data)
			{
				printf("REJECTED\n");
				delete_linked_list(head_input_list2);
				delete_linked_list(head_output_list);
				break;
			}
			input_list2 = input_list2->next;
			output_list = output_list->next;
		
		}
		if(input_list2 ==NULL && output_list ==NULL)
		{
			printf("ACCEPTED\n");
			delete_linked_list(head_input_list2);
			delete_linked_list(head_output_list);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_merging_sorted_linked_lists();
	getchar();
	return 0;
}