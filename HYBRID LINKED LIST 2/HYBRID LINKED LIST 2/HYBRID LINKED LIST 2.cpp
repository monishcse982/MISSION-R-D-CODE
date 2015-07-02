// HYBRID LINKED LIST 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *next;
	NODE *k_next;
};

int create_linked_list(int *input_array, int length, NODE *head)
{
	int iter_loop=1,k_offset=0;;
	while((iter_loop*iter_loop)<=length)
	{
		iter_loop++;
	}
	k_offset = iter_loop-1;
	iter_loop = 0;
	head->data = input_array[iter_loop];
	head->next = head->k_next = NULL;
	NODE *temp = head;
	NODE *previous = temp;
	iter_loop++;
	while(iter_loop<length)
	{
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		new_node->data = input_array[iter_loop];
		new_node->next = NULL;
		temp->next = new_node;
		temp = new_node;
		if(iter_loop%k_offset==0)
		{
			previous->k_next = temp;
			previous = temp;
		}
		temp->k_next = NULL;
		iter_loop++;
	}
	return k_offset;
}

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

int* update_segment_table(int* segment_table, NODE*head,int* k_offset, int segment_number, int *segment_table_size, int *length)
{
	if(segment_table[segment_number]>=*k_offset)
	{
		segment_table = (int*)realloc(segment_table,(*segment_table_size+1)*sizeof(int));
		for(int iter_loop=0;iter_loop<*segment_table_size;iter_loop++)
		{
			segment_table[iter_loop] = 0;
		}
		*k_offset = *k_offset+1;
	}
	int iter_loop=1;
	while((iter_loop*iter_loop)<=*length)
	{
		iter_loop++;
	}
	iter_loop--;
	if(*k_offset == iter_loop)
	{
		return k_offset;
	}
	else if(*k_offset<iter_loop)
	{
		*k_offset = iter_loop;
		int iter_loop=0;
		NODE *temp = head;
		while(temp!=NULL && temp->k_next!=NULL)
			{				
				NODE *next = temp->k_next;
				temp->k_next = NULL;
				temp = next;
			}
		temp = head->next;
			iter_loop=1;
			NODE *previous = head;
			while(temp!=NULL)
			{
				if(iter_loop%(*k_offset)==0)
				{
					previous->k_next = temp;
					previous = temp;
				}
				temp->k_next = NULL;
				iter_loop++;
				temp = temp->next;
			}
		return k_offset;
	}
}

NODE* insert_into_linked_list(NODE *head, int key, int *length, int *segment_table, int *k_offset)
{
	int segment_number=0;
	if(head->data == key)
	{
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		new_node->data = key;
		new_node->next = head;
		new_node->k_next = head->k_next;
		segment_table[segment_number] +=1; 
		*length = *length+1;
		k_offset = update_segment_table(segment_table, head, k_offset, segment_number, segment_table, length);
		return new_node;
	}
	else if(head->data<key)
	{
		NODE *temp = head;
		while(temp->k_next!=NULL && temp->k_next->data<key)
		{
			temp = temp->k_next;
			segment_number++;
		}
		while(temp->next!=NULL && temp->next->data<=key)
		{
			temp = temp->next;
			if(temp->data==-1)
			{
				temp->data = key;
				segment_table[segment_number] +=1;
				*length = *length+1;
				k_offset = update_segment_table(segment_table, head, k_offset, segment_number, segment_table, length);
				return head;
			}
		}
		if(temp->data!=-1)
		{
			NODE *new_node = (NODE*)malloc(sizeof(NODE));
			new_node->data = key;
			new_node->next = temp->next;
			temp->next = new_node;
		}
		segment_table[segment_number] +=1;
		*length = *length+1;
		k_offset = update_segment_table(segment_table, head, k_offset, segment_number, segment_table, length);
		return head;
	}
	else if(head->data>key)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		temp->data = key;
		temp->next = head;
		temp->k_next = head->k_next;
		head->k_next = NULL;
		head = temp;
		segment_table[segment_number] +=1;
		*length = *length+1;
		k_offset = update_segment_table(segment_table, head, k_offset, segment_number, segment_table, length);
		return head;
	}
}

int shuffle_the_linked_list_after_delete(int* segment_table, NODE *head, int* k_offset, int segment_number, int *segment_table_size, int *length)
{
	if(segment_table[segment_number]<(-(*k_offset)))
	{
		*segment_table_size = *segment_table_size - 1;;
		for(int iter_loop=0;iter_loop<*segment_table_size;iter_loop++)
		{
			segment_table[iter_loop] = 0;
		}
	}
	int iter_loop=1;
	while ((iter_loop*iter_loop)<=*length)
	{
		iter_loop++;
	}
	iter_loop--;
	if(*k_offset==iter_loop)
	{
		return *k_offset;
	}
	else if(*k_offset!=iter_loop)
	{
		*k_offset=iter_loop;
		NODE *temp = head;
		if(temp->data==-1)
		{
			NODE *previous = temp;
			temp = temp->next;

			while(temp!=NULL && temp->next->data==-1)
			{
				temp = temp->next;
			}
			head = temp->next;
			temp->next=NULL;
			delete_linked_list(previous);
		}
		while(temp!=NULL)
		{
			if(temp->next->data!=-1)
			{
				temp = temp->next;
				continue;
			}
			if(temp->next->data==-1)
			{
				NODE *previous = temp;
				temp = temp->next;
				while(temp!=NULL && temp->next!=NULL && temp->next->data==-1)
				{
					temp = temp->next;
				}
				NODE *delete_list = previous->next;
				previous->next = temp->next;
				NODE *next = temp->next;
				temp->next=NULL;
				temp = next;
				delete_linked_list(delete_list);
			}
		}
	}
	NODE *temp = head;
		while(temp!=NULL)
			{
				temp->k_next = NULL;
				temp = temp->k_next;
			}
		temp = head;
		iter_loop=0;
		NODE *previous = head;
		while(temp!=NULL)
		{
			if(iter_loop%*k_offset==0)
			{
				previous->k_next = temp;
				previous = temp;
			}
			temp->k_next = NULL;
			iter_loop++;
			temp = temp->next;
		}
		return *k_offset;
}

NODE* delete_from_linked_list(NODE *head, int key, int *length, int *k_offset, int *segment_table, int segment_table_size)
{
	int segment_number = 0;
	if(head->data == key)
	{
		NODE *temp = head;
		if(head->k_next!=NULL)
		{
			head->next->k_next = head->k_next;
			head = head->next;
		}
		free(temp);
		*length = *length-1;
		shuffle_the_linked_list_after_delete(segment_table, head, k_offset, segment_number, &segment_table_size, length);
		return head;
	}
	else if(head->data != key)
	{
		NODE *temp = head;
		while(temp->k_next!=NULL && temp->k_next->data<key)
		{
			temp = temp->k_next;
			segment_number++;
		}
		while(temp->next!=NULL)
		{
			if(temp->next->data == key && temp->next->k_next == NULL)
			{
				NODE *next = temp->next->next;
				free(temp->next);
				temp->next = next;
				break;
			}
			else if(temp->next->data == key && temp->next->k_next != NULL)
			{
				temp->next->data = -1;
				break;
			}
			else if(temp->next->data<key)
			{
				temp = temp->next;
			}
		}
		segment_table[segment_number]-=1;
		*length = *length-1;
		*k_offset = shuffle_the_linked_list_after_delete(segment_table, head, k_offset, segment_number, &segment_table_size, length);
		return head;
	}
}

void print_linked_list(NODE *head)
{
	while(head->next!=NULL)
	{
		printf("%d,",head->data);
		head = head->next;
	}
	printf("%d",head->data);
}

void print_k_nodes(NODE *head)
{
	while(head!=NULL)
	{
		printf("%d->",head->data);
		head = head->k_next;
	}
}

void display(NODE *head)
{
	print_linked_list(head);
	printf("\n");
	print_k_nodes(head);
}

void driver_for_hybrid_linked_list(int *input_array, int length)
{
	NODE *head = (NODE*)malloc(sizeof(NODE));
	int k_offset = create_linked_list(input_array, length, head);
	int *segment_table = (int*)calloc((length/k_offset),sizeof(int));
	display(head);
	int segment_table_size=(length/k_offset);
	for(int iter_loop=0;iter_loop<(length/k_offset);iter_loop++)
	{
		segment_table[iter_loop] = 0;
	}
	int insert_value;
	
	printf("K: %d",k_offset);
	printf("\nINSERT SOME VALUES: ");
	scanf_s("%d",&insert_value);
	head = insert_into_linked_list(head, insert_value,&length, segment_table, &k_offset);
	display(head);
	printf("K: %d",k_offset);
	printf("\nINSERT SOME VALUES: ");
	scanf_s("%d",&insert_value);
	head = insert_into_linked_list(head, insert_value,&length, segment_table, &k_offset);
	display(head);
	printf("K: %d",k_offset);
	printf("\nINSERT SOME VALUES: ");
	scanf_s("%d",&insert_value);
	head = insert_into_linked_list(head, insert_value,&length, segment_table, &k_offset);
	display(head);
	printf("K: %d",k_offset);
	printf("\nINSERT SOME VALUES: ");
	scanf_s("%d",&insert_value);
	head = insert_into_linked_list(head, insert_value,&length, segment_table, &k_offset);
	display(head);
	printf("K: %d",k_offset);
	printf("\nINSERT SOME VALUES: ");
	scanf_s("%d",&insert_value);
	head = insert_into_linked_list(head, insert_value,&length, segment_table, &k_offset);
	display(head);
	printf("K: %d",k_offset);
	printf("\nDELETE SOME VALUES: ");
	scanf_s("%d",&insert_value);
	head = delete_from_linked_list(head, insert_value,&length, segment_table, &k_offset, segment_table_size);
	display(head);
	printf("K: %d",k_offset);
	printf("\nDELETE SOME VALUES: ");
	scanf_s("%d",&insert_value);
	head = delete_from_linked_list(head, insert_value,&length, segment_table, &k_offset, segment_table_size);
	display(head);
	printf("K: %d",k_offset);
	printf("\nDELETE SOME VALUES: ");
	scanf_s("%d",&insert_value);
	head = delete_from_linked_list(head, insert_value,&length, segment_table, &k_offset, segment_table_size);
	display(head);
	printf("K: %d",k_offset);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int input_array[10] = {10,20,30,40,50,60,70,80,90};
	driver_for_hybrid_linked_list(input_array, 9);
	getchar();
	return 0;
}