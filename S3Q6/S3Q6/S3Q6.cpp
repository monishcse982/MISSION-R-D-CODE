// S3Q6.cpp : A boy can climb 1 or 2 steps at a time, how many ways can he climb n stairs.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	char data;
	NODE *next;
};

NODE* delete_node(NODE* head)
{
	if(head->next==NULL)
	{
		free(head);
		return NULL;
	}
	NODE* duplicate_head = head;
	while(head->next!=NULL && head->next->next!=NULL)
	{
		head = head->next;
	}
	NODE* temp = head->next;
	free(temp);
	head->next = NULL;
	return duplicate_head;
}

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
	NODE* temp = input;
	while(temp->next!=NULL)
	{
		printf("%c->",temp->data);
		temp = temp->next;
	}
	printf("%c\n",temp->data);
	return input;
}

NODE* append_node(NODE* head, char data)
{
	if(head==NULL)
	{
	NODE* duplicate_head = head;
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = NULL;
	head = temp;
	return head;
	}
	NODE* duplicate_head = head;
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->next = NULL;
	while(head->next!=NULL)
	{
		head = head->next;
	}
	head->next = temp;
	return duplicate_head;
}

int n_stairs(int no_of_steps)
{
	if(no_of_steps==0)
	{
		return 0;
	}
	else if(no_of_steps==1)
	{
		return 1;
	}
	else if(no_of_steps==2)
	{
		return 2;
	}
	else if(no_of_steps>2)
	{
		return n_stairs(no_of_steps-1) + n_stairs(no_of_steps-2);
	}
}

void no_of_ways_of_n_stairs(int no_of_steps, NODE* list)
{
	if(no_of_steps==0)
	{
		list = print_linked_list(list);
		return;
	}
	else if(no_of_steps==1)
	{
		list = append_node(list,'S');
		no_of_ways_of_n_stairs(0,list);
		list = delete_node(list);
		return;
	}
	else if(no_of_steps==2)
	{
		list = append_node(list,'S');
		list = append_node(list,'S');
		list = print_linked_list(list);
		list = delete_node(list);
		list = delete_node(list);
		list = append_node(list,'D');
		list = print_linked_list(list);
		list = delete_node(list);
		return;
	}
	else if(no_of_steps>2)
	{
		list = append_node(list,'D');
		no_of_ways_of_n_stairs(no_of_steps-2,list);
		list = delete_node(list);
		list = append_node(list,'S');
		no_of_ways_of_n_stairs(no_of_steps-1,list);
		list = delete_node(list);
		return;
	}
}

void test_n_stairs()
{
	int input[] = {1,2,3,4,5,6};
	int iter_loop;
	for(iter_loop=0;iter_loop<6;iter_loop++)
	{
		printf("NO OF WAYS OF CLIMBING %d STEPS IS: %d\n",input[iter_loop],n_stairs(input[iter_loop]));
		printf("WAYS OF CLIMBING %d STEPS ARE:\n",input[iter_loop]);
		NODE* list=NULL;
		no_of_ways_of_n_stairs(input[iter_loop],list);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_n_stairs();
	getchar();
	return 0;
}