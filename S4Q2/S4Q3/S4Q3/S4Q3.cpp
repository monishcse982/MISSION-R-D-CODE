// S4Q3.cpp : Given an unsorted linked list as input, sort the linked list. dont use values to move, use pointers to make it sorted
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

NODE* merge_sorted_linked_lists(NODE *list1, NODE *list2)
{
	if(list1 == NULL && list2 == NULL)
	{
		return NULL;
	}
	else if(list1 == NULL && list2 != NULL)
	{
		return list2;
	}
	else if(list1 != NULL && list2 == NULL)
	{
		return list1;
	}

	NODE *return_head = list2;

	if(list1->data < list2->data)
	{
		return_head = list1;
	}
	else if(list1->data > list2->data)
	{
		return_head = list2;
	}

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
			return list2;
		}
	}
	while(list1!=NULL)
	{
		NODE *temp_list1 = list1->next;
		if(list1->data <= list2->data)
		{
			list1->next = list2;
			return return_head;
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
				return return_head;
			}
		}
		list1 = temp_list1;
	}
	return  return_head;
}

NODE* partition_linked_list(NODE* head)
{
	if(head->next == NULL)
	{
		return head;
	}
	NODE *slow = head, *fast = head;
	while(fast->next!=NULL && fast->next->next!=NULL)
	{
		if(fast->next->next->next==NULL)
		{
			break;
		}
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

NODE* sort_linked_list(NODE* head)
{
	if(head == NULL || head->next == NULL)
	{
		return head;
	}

	NODE *partition_node = partition_linked_list(head);
	NODE *second_half = partition_node->next;
	partition_node->next = NULL;
	partition_node = second_half;
	head = sort_linked_list(head);
	partition_node = sort_linked_list(partition_node);
	head = merge_sorted_linked_lists(head,partition_node);
	return head;
}

void test_sort_linked_list()
{
	int input_array[8][10]  = {{9, 8, 7, 6, 5, 4, 3, 2, 1},{34, 76, 23, 98, 43},{2,1},{1},{NULL},{8, 7, 6, 5, 4, 3, 2, 1},{3,2,1},{236,235,440,100}};
	int output_array[8][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9},{23, 34, 43, 76, 98},{1,2},{1},{NULL},{1, 2, 3, 4, 5, 6, 7, 8},{1,2,3},{100, 235, 236, 440}};
	int iter_loop;
	for(iter_loop=0;iter_loop<8;iter_loop++)
	{
		NODE *input_list = create_linked_list(input_array[iter_loop]);
		NODE *output_list = create_linked_list(output_array[iter_loop]);
		input_list = sort_linked_list(input_list);
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
	test_sort_linked_list();
	getchar();
	return 0;
}