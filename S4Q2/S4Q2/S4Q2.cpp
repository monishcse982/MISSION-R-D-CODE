// S4Q2.cpp : Given a sorted linked list as input (remember you have to create this in your program using the test stub and the above program) and a value, write a. add the element to the linked list if it doesnt exist b. delete the element from the linked list if it exists
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
	NODE *next;
	while(head->next!=NULL)
	{
		next = head->next;
		free(head);
		head = next;
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
	if(input == NULL)
	{
		printf("NO INPUT\n");
		return input;
	}
	NODE* temp = input;
	while(temp->next!=NULL)
	{
		printf("%d->",temp->data);
		temp = temp->next;
	}
	printf("%d\n",temp->data);
	return input;
}

NODE* insert_delete_node(NODE *input_list, int key)
{
	if(input_list == NULL)
	{
		return NULL;
	}
	if(key == NULL)
	{
		return input_list;
	}
	if(input_list->next == NULL && key == input_list->data)
	{
		free(input_list);
		return NULL;
	}
	if(input_list->data > key)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		temp->data = key;
		temp->next = input_list;
		input_list = temp;
		return input_list;
	}
	if(input_list->data == key)
	{
		NODE *temp = input_list;
		input_list = input_list->next;
		free(temp);
		return input_list;
	}
	NODE *head_duplicate = input_list;
	while(input_list->next!=NULL && input_list->next->data <= key)
	{
		if(input_list->next->data == key)
		{
			NODE* temp = input_list->next;
			input_list->next = input_list->next->next;
			free(temp);
			return head_duplicate;
		}
		input_list = input_list->next;
	}
	NODE *temp = (NODE*)malloc(sizeof(NODE));
	temp->data = key;
	temp->next = input_list->next;
	input_list->next = temp;
	return head_duplicate;
}

void test_insert_delete_node()
{
	int input_array[12][10] = {{23,32,57,64},{2,14,20,64,146},{1,3,7,12,35,52,72,91},{23},{NULL},{90,91,92},{67,74,153,262},{23,45},{36,47,53,69},{12,14,25,66,91},{-9,-8,-7,-6,-5,4,3,2,1},{1,2,3,4,5,6,7,8,9}};

	int key[12] = {64,2,25,23,3,3,265,32,268,2,5,-5};

	int output[12][10] = {{23,32,57},{14,20,64,146},{1,3,7,12,25,35,52,72,91},{NULL},{NULL},{3,90,91,92},{67,74,153,262,265},{23,32,45},{36,47,53,69,268},{2,12,14,25,66,91},{-9,-8,-7,-6,-5,4,3,2,1},{-5,1,2,3,4,5,6,7,8,9}};

	int iter_loop;
	for(iter_loop=0;iter_loop<12;iter_loop++)
	{
		NODE *input_list = create_linked_list(input_array[iter_loop]);
		NODE *output_list = create_linked_list(output[iter_loop]);
		input_list = insert_delete_node(input_list,key[iter_loop]);
		NODE *input_list_duplicate = input_list;
		NODE *output_list_duplicate = output_list;
			while(input_list!=NULL || output_list!=NULL)
			{
				if(input_list == NULL || output_list== NULL)
				{
					printf("ACCEPTED\n");
					break;
				}
				if(input_list->data!= output_list->data)
				{
					printf("REJECTED\n");
					delete_linked_list(input_list_duplicate);
					delete_linked_list(output_list_duplicate);
					break;
				}
				input_list = input_list->next;
				output_list = output_list->next;
			}
			if(input_list==NULL && output_list==NULL)
			{
				printf("ACCEPTED\n");
				delete_linked_list(input_list_duplicate);
				delete_linked_list(output_list_duplicate);
			}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_insert_delete_node();
	getchar();
	return 0;
}