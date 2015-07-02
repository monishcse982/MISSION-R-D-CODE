// STRING TO LINKED LIST.cpp : Given a string which has values of integers comma seperated, create a linked list. example "123,34,456,7893,321" output list as: 123->34->456->7893->321
//

#include "stdafx.h"
#include "stdlib.h"

int string_length(char* input_array)
{
	int iter_loop=0;

	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

int exponent(int base, int power)
{
	if(power == 0)
	{
		return 1;
	}
	int result=1, iter_loop;
	for(iter_loop=0;iter_loop<power;iter_loop++)
	{
		result *= base;
	}
	return result;
}

int create_number(char *input_array, int start, int end)
{
	int iter_loop = end,result=0,power=0;
	while(iter_loop>=start)
	{
		if(!(input_array[iter_loop]>='0' && input_array[iter_loop]<='9'))
		{
			return NULL;
		}
		result += (input_array[iter_loop] & ('p'-'a')) * exponent(10,power);
		power++;
		iter_loop--;
	}
	return result;
}

struct NODE
{
	int data;
	NODE *next;
};

void delete_linked_list(NODE *head)
{
	if(head == NULL)
	{
		return;
	}
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

NODE* create_node(int data)
{
	NODE* head = (NODE*)malloc(sizeof(NODE));
	head->data = data;
	return head;
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

NODE* string_to_linked_list(char *input_array)
{
	if(input_array == NULL)
	{
		return NULL;
	}
	int data;
	int iter_loop=0, iter_loop2=0;
	NODE *head=NULL, *temp=NULL;
	while(input_array[iter_loop]!='\0')
	{
	while(input_array[iter_loop2]!=',' && input_array[iter_loop2]!='\0')
	{
		iter_loop2++;
	}
	data  = create_number(input_array, iter_loop, iter_loop2-1);
	if(data == NULL)
	{
		if(input_array[iter_loop2]!='\0')
		{
			iter_loop2++;
		}
		else if(input_array[iter_loop2]=='\0')
		{
			return NULL;
		}
		iter_loop = iter_loop2;
		continue;
	}
	head = create_node(data);
	temp = head;
	temp->next = NULL;
	if(input_array[iter_loop2]!='\0')
	{
		iter_loop2++;
	}
	iter_loop = iter_loop2;
	break;
	}
	while(input_array[iter_loop]!='\0')
	{
		while(input_array[iter_loop2]!=',' && input_array[iter_loop2]!='\0')
		{
			iter_loop2++;
		}
		data = create_number(input_array, iter_loop, iter_loop2-1);
		if(data == NULL)
		{
			if(input_array[iter_loop2]!='\0')
			{
				iter_loop2++;
			}
		else if(input_array[iter_loop2]=='\0')
		{
			return NULL;
		}
			iter_loop = iter_loop2;
			continue;
		}
		NODE *new_node = create_node(data);
		temp->next  = new_node;
		temp = new_node;
		temp->next = NULL;
		if(input_array[iter_loop2]=='\0')
		{
			break;
		}
		else if(input_array[iter_loop2]!='\0')
		{
			iter_loop = ++iter_loop2;
		}
	}
	return head;
}

void test_string_to_linked_list()
{
	char input[8][30] = {"123,34,456,7893,321",
								"1,2,3,4,5,6,7,8,9",
								"1",
								"12a,123g,456,78R9",
								"214r,1,2,3,4,5,6474y",
								"44561a",
								"1q,2w,3e,4r,5,6,7,8i,9o,7p",
								NULL,
							  };
	int output[8][10] = {{123,34,456,7893,321},{1,2,3,4,5,6,7,8,9},{1},{456},{1,2,3,4,5},{NULL},{5,6,7},{NULL}};
	int iter_loop;
	for(iter_loop=0;iter_loop<8;iter_loop++)
	{
		NODE *input_list = string_to_linked_list(input[iter_loop]);
		NODE *output_list = create_linked_list(output[iter_loop]);
		NODE *head_input_list = input_list;
		NODE *head_output_list = output_list;
		if(input_list==NULL || output_list==NULL)
		{
			printf("ACCEPTED\n");
			continue;
		}
		while(input_list!=NULL || output_list!=NULL)
		{
			if(input_list->data!=output_list->data)
			{
				printf("REJECTED\n");
				delete_linked_list(head_input_list);
				delete_linked_list(head_output_list);
			}
			input_list = input_list->next;
			output_list = output_list->next;
		}
		if(input_list==NULL && output_list==NULL)
		{
			printf("ACCEPTED\n");
			delete_linked_list(head_input_list);
			delete_linked_list(head_output_list);
			
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_string_to_linked_list();
	getchar();
	return 0;
}