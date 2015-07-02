// COMPARE 4 FIELDS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	int v1;
	int v2;
	char *s1;
	char *s2;
	NODE *next;
};

NODE* create_linked_list(int* v1, int* v2, char **s1, char **s2, int length)
{
	int iter_loop=0;
	NODE *head = (NODE*)malloc(sizeof(NODE));
	head->v1 = v1[iter_loop];
	head->v2 = v2[iter_loop];
	head->s1 = s1[iter_loop];
	head->s2 = s2[iter_loop];
	NODE *temp = head;
	head->next = NULL;
	iter_loop++;
	while(iter_loop <length)
	{
		NODE *new_node = (NODE*)malloc(sizeof(NODE));
		new_node->v1 = v1[iter_loop];
		new_node->v2 = v2[iter_loop];
		new_node->s1 = s1[iter_loop];
		new_node->s2 = s2[iter_loop];
		new_node->next = NULL;
		temp->next = new_node;
		temp = new_node;
	}
}

int string_compare(char *string1, char *string2)
{
	int iter_loop=0;
	while(string1[iter_loop]!='\0' && string2[iter_loop]!='\0')
	{
		if(string1[iter_loop+1]=='\0' && string2[iter_loop+1]!='\0')
		{
			return 1;
		}
		else if(string1[iter_loop+1]!='\0' && string2[iter_loop+1]=='\0')
		{
			return -1;
		}
		else if(string1[iter_loop]>string2[iter_loop])
		{
			return -1;
		}
		else if(string1[iter_loop]<string2[iter_loop])
		{
			return 1;
		}
		else if((string1[iter_loop]==string2[iter_loop]) && string1[iter_loop+1]!='\0')
		{
			continue;
		}
		else if((string1[iter_loop]==string2[iter_loop]) && string1[iter_loop+1]=='\0')
		{
			return 0;
		}
	}
}

void sort_with_multiple_values(NODE *head)
{
	
}

void test_compare_4_fields()
{
	int input_v1[5][10][1] =  {
	{{21},{34},{56},{46},{78},{92},{3},{101},{50},{96}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	};
	int output_v1[5][10][1] = {
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	};

	int input_v2[5][10][1] =  {
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	};
	int output_v2[5][10][1] = {
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	{{},{},{},{},{},{},{},{},{},{}},
	};

	char input_s1[5][10][21] = {{"","","","",""},{"","","","",""},{"","","","",""},{"","","","",""},{"","","","",""}};
	char output_s1[5][10][21] = {{"","","","",""},{"","","","",""},{"","","","",""},{"","","","",""},{"","","","",""}};

	char input_s2[5][10][101]   =  {{"","","","",""},{"","","","",""},{"","","","",""},{"","","","",""},{"","","","",""}};
	char output_s2[5][10][101]  = {{"","","","",""},{"","","","",""},{"","","","",""},{"","","","",""},{"","","","",""}};

	int length_of_inputs[5] = {};
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}