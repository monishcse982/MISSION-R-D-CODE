// HYBRID LINKED LIST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int data;
	NODE *next;
	NODE *k_next;
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

int shuffle_the_linked_list_after_insert(NODE *head, int k_offset, int *length)
{
	int iter_loop=1;
	while ((iter_loop*iter_loop)<=*length)
	{
		iter_loop++;
	}
	iter_loop--;
	if(k_offset==iter_loop)
	{
		return k_offset;
	}
	else if(k_offset!=iter_loop)
	{
		k_offset = iter_loop;
		NODE *temp = head;
		while(temp!=NULL && temp->k_next!=NULL)
			{
				temp->k_next = NULL;
				temp = temp->k_next;
			}
		temp = head;
		iter_loop=0;
		NODE *previous = head;
		while(temp!=NULL)
		{
			if(iter_loop%k_offset==0)
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

int shuffle_the_linked_list_after_delete(NODE *head, int k_offset, int *length)
{
	int iter_loop=1;
	while ((iter_loop*iter_loop)<=*length)
	{
		iter_loop++;
	}
	iter_loop--;
	if(k_offset==iter_loop)
	{
		return k_offset;
	}
	else if(k_offset!=iter_loop)
	{
		k_offset=iter_loop;
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
			if(iter_loop%k_offset==0)
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

int create_linked_list(int *input_array, int length, NODE *head)
{
	int iter_loop=1,k_offset=0;;
	while((iter_loop*iter_loop)<length)
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
	while(iter_loop<length-1)
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

NODE* insert_into_linked_list(NODE *head, int key, int *length)
{
	if(head->data == key)
	{
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		new_node->data = key;
		new_node->next = head;
		new_node->k_next = head->k_next;
		head->k_next = NULL;
		head = new_node;
		return head;
	}
	else if(head->data<key)
	{
		NODE *temp = head;
		while(temp->next!=NULL && temp->next->data<=key)
		{
			temp = temp->next;
			if(temp->data==-1)
			{
				temp->data = key;
				return head;
			}
		}
		if(temp->data!=-1)
		{
			NODE *new_node = (NODE*)malloc(sizeof(NODE));
			new_node->data = key;
			new_node->next = temp->next;
			temp->next = new_node;
			if(new_node->next!=NULL && new_node->next->k_next!=NULL)
			{
				new_node->k_next = new_node->next->k_next;
			}
		}
		return head;
	}
}

NODE* delete_from_linked_list(NODE *head, int key, int *length)
{
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
		return head;
	}
	else if(head->data != key)
	{
		NODE *temp = head;
		while(temp->next!=NULL)
		{
			if(temp->k_next!=NULL && temp->k_next->data<key)
			{
				temp = temp->k_next;
				continue;
			}
			else if(temp->k_next!=NULL && temp->k_next->data==key)
			{
				temp->k_next->data = -1;
				return head;
			}
			else if(temp->next!=NULL && temp->next->data==key)
			{
				temp->next->data = -1;
				return head;
			}
			temp = temp->next;
		}
		temp->next->data = -1;
		*length = *length-1;
		return head;
	}

}

int search_linked_list(NODE *head, int key)
{
	if(head->data == key)
	{
		return 1;
	}
	else if(head->data!=key)
	{
		if(head->k_next!=NULL)
		{
			if( head->k_next->data==key)
			{
				return 1;
			}
			else if(head->k_next->data>key)
			{
				return (search_linked_list(head->next,key));
			}
			else if(head->k_next->data<key)
			{
				if(head->k_next->data!=-1)
				{
					return (search_linked_list(head->k_next,key));
				}
				else
				{
					return (search_linked_list(head->next,key));
				}
			}
		}
		else if(head->k_next==NULL)
		{
			return (search_linked_list(head->next,key));
		}
	}
}

void display(NODE *head)
{
	print_linked_list(head);
	printf("\n");
	print_k_nodes(head);
}

NODE* driver_for_hybrid_list(int* input, int *length)
{
	NODE *head = (NODE*)malloc(sizeof(NODE));
	head->next=NULL;
	head->k_next=NULL;
	int k_offset = create_linked_list(input,*length,head);
	display(head);
	int insert_value;
	printf("--LENGTH: %d--",*length-1);
	printf("ENTER VALUE TO BE INSERTED:\t");
	scanf_s("%d",&insert_value);
	head = insert_into_linked_list(head,insert_value, length);
	*length = *length+1;
	k_offset = shuffle_the_linked_list_after_insert(head, k_offset, length);
	display(head);
	printf("--LENGTH: %d--",*length-1);
	printf("ENTER VALUE TO BE INSERTED:\t");
	scanf_s("%d",&insert_value);
	head = insert_into_linked_list(head,insert_value,length);
	*length = *length+1;
	k_offset = shuffle_the_linked_list_after_delete(head, k_offset, length);
	display(head);
	printf("--LENGTH: %d--",*length-1);
	printf("ENTER VALUE TO BE DELETED:\t");
	scanf_s("%d",&insert_value);
	head = delete_from_linked_list(head,insert_value, length);
	*length = *length-1;
	k_offset = shuffle_the_linked_list_after_delete(head, k_offset, length);
	display(head);
	printf("--LENGTH: %d--",*length-1);
	printf("ENTER VALUE TO BE DELETED:\t");
	scanf_s("%d",&insert_value);
	head = delete_from_linked_list(head,insert_value, length);
	*length = *length-1;
	k_offset = shuffle_the_linked_list_after_delete(head, k_offset, length);
	display(head);
	delete_linked_list(head);
	return head;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int input[10] = {1,2};
	int length = 3;
	driver_for_hybrid_list(input,&length);
	getchar();
	return 0;
}