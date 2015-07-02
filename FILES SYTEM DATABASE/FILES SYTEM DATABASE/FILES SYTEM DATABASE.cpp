// FILES SYTEM DATABASE.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#define NO_OF_RECORDS 300
#define SIZE_OF_RECORD 16

struct RECORD
{
	char name[120];
	int roll_no;
	int marks;
	char address[128];
	RECORD *next;
};

int string_length(char* input_array)
{
	int iter_loop=0;

	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

RECORD* copy_data(RECORD details)
{
	int iter_loop=0;
	RECORD *new_node = (RECORD*)malloc(sizeof(RECORD));
	details.marks = new_node->marks;
	details.roll_no = new_node->roll_no;
	for(iter_loop=0;details.address[iter_loop]!='\0';iter_loop++)
	{
		new_node->address[iter_loop] = details.address[iter_loop];
	}
	new_node->address[iter_loop] = details.address[iter_loop];
	for(iter_loop=0;details.name[iter_loop];iter_loop++)
	{
		new_node->address[iter_loop] = details.address[iter_loop];
	}
	new_node->address[iter_loop] = details.address[iter_loop];
	new_node->next = NULL;
	return new_node;
}

int exponent(int base, int power)
{
	int result=1, iter_loop;
	for(iter_loop=0;iter_loop<power;iter_loop++)
	{
		result *= base;
	}
	return result;
}

void print_record(RECORD details)
{
	printf("----------------------\n");
	printf("%d\n",details.roll_no);
	printf("%s\n",details.name);
	printf("%d\n",details.marks);
	printf("%s\n",details.address);
}

int ASCII_TO_INT(char* input_array)
{
	int length = string_length(input_array)-1, result_integer=0, iter_loop = length,negative_input_flag=0;

	if(input_array[0] == '-')
	{
		negative_input_flag++;
	}

	while (input_array[iter_loop]!=' ')
	{
		if(negative_input_flag == 1 && iter_loop==0)
		{
			break;
		}
		if(input_array[iter_loop]<'0' && input_array[iter_loop]>'9')
		{
			printf("INVALID INPUT\n");
			return 0;
		}
		result_integer += (input_array[iter_loop] & ('p'-'a')) * exponent(10,length - iter_loop);
		iter_loop--;
	}

	if(negative_input_flag == 1)
	{
		return -result_integer;
	}
	else if(negative_input_flag == 0)
	{
		return result_integer;
	}
}

int string_compare(char *string1, char *string2)
{
	int index = 0;
	while(string1[index]!='\0' && string1[index]!='\0')
	{
		if(string1[index]!=string2[index])
		{
			return -1;
		}
		index++;
	}
	return 1;
}

RECORD string_query_processing(RECORD *details, int operator_key, char *query, int index, int no_of_records)
{
	RECORD *final_result_set = NULL;
	RECORD *temp = NULL;
	int record_found = 0;
	index++;
	if((query[index] =='s' && query[index+1] == 'w') || (query[index] =='S' && query[index+1] == 'W'))
	{
		RECORD *head = (RECORD*)malloc(sizeof(RECORD));
		index = index+3;
		char *search_key = (char*)calloc(1,sizeof(char));
		int search_index = 0;
		while(query[index]!='\0')
		{
			search_key = (char*)realloc(search_key,(search_index+2)*sizeof(char));
			search_key[search_index] = query[index];
			index++;
			search_index++;
		}
		search_key[search_index] = '\0';
		int details_key = 0;
		index = 0;
		if(operator_key == 1)
		{
			while(details_key<no_of_records)
			{
				while(search_key[index]!='\0')
				{
					if(details[details_key].name[index] != search_key[index])
					{
						break;
					}
					index++;
				}
				if(search_key[index] == '\0' && (search_key[index-1] == details[details_key].name[index-1]))
				{
					RECORD *result_set;
					int iter_loop = 0;
					result_set = copy_data(details[details_key]);
					if(temp!=NULL)
					{
						temp->next = result_set;
					}
					temp = result_set;
					temp->next = NULL;
					record_found++;
				}
				index = 0;
				details_key++;
			}
			free(search_key);
		}
		else if(operator_key == 2)
		{
			while(details_key<no_of_records)
			{
				while(search_key[index]!='\0')
				{
					if(details[details_key].address[index] != search_key[index])
					{
						break;
					}
					index++;
				}
				if(search_key[index] == '\0' && (search_key[index-1] == details[details_key].address[index-1]))
				{
					RECORD *result_set;
					int iter_loop = 0;
					result_set = copy_data(details[details_key]);
					if(temp!=NULL)
					{
						temp->next = result_set;
					}
					temp = result_set;
					temp->next = NULL;
					record_found++;
				}
				index = 0;
				details_key++;
			}
			free(search_key);
		}
	}
	else if((query[index] =='e' && query[index+1] == 'w') || (query[index] =='E' && query[index+1] == 'W'))
	{
		index = index+3;
		char *search_key = (char*)calloc(1,sizeof(char));
		int search_index = 0;
		while(query[index]!='\0')
		{
			search_key = (char*)realloc(search_key,(search_index+2)*sizeof(char));
			search_key[search_index] = query[index];
			index++;
			search_index++;
		}
		search_key[search_index] = '\0';
		int details_key = 0;
		search_index--;
		index = search_index;
		if(operator_key == 1)
		{
			RECORD *result_set = (RECORD*)malloc(sizeof(RECORD));
			while(details_key<no_of_records)
			{
				int string_index = strlen(details[details_key].name)-1;
				while(index>=0)
				{
					if(details[details_key].name[string_index] != search_key[index])
					{
						break;
					}
					index--;
					string_index--;
				}
				if(index == -1 && (search_key[index+1] == details[details_key].name[string_index+1]))
				{
					RECORD *result_set;
					int iter_loop = 0;
					result_set = copy_data(details[details_key]);
					if(temp!=NULL)
					{
						temp->next = result_set;
					}
					temp = result_set;
					temp->next = NULL;
					record_found++;
				}
				index = search_index;
				details_key++;
			}
			free(search_key);
		}
		else if(operator_key == 2)
		{
			while(details_key<no_of_records)
			{
				int string_index = strlen(details[details_key].name)-1;
				while(search_key[index]!='\0')
				{
					if(details[details_key].address[string_index] != search_key[index])
					{
						break;
					}
					string_index--;
					index--;
				}
				if(index == 0 && (search_key[index+1] == details[details_key].address[string_index+1]))
				{
					RECORD *result_set = (char*)malloc(sizeof(RECORD));
					result_set->marks = details[details_key].marks;
					result_set->roll_no = details[details_key].roll_no;
					int iter_loop = 0;
					for(iter_loop=0;details[details_key].address[iter_loop]!='\0';iter_loop++)
					{
						result_set->address[iter_loop] = details[details_key].address[iter_loop];
					}
					result_set->address[iter_loop] = details[details_key].address[iter_loop];
					for(iter_loop=0;details[details_key].name[iter_loop]!='\0';iter_loop++)
					{
						result_set->name[iter_loop] = details[details_key].name[iter_loop];
					}
					result_set->name[iter_loop] = details[details_key].name[iter_loop];
					record_found++;
					result_set->next= NULL;
					temp->next = result_set;
					temp = temp->next;
				}
				index = search_index;
				details_key++;
			}
			free(search_key);
			return final_result_set;
		}
	}
	return result_set;
}

RECORD numeric_query_processing(RECORD *details, int operator_key, char *query, int index, int no_of_records, RECORD result_set)
{
	int record_found=0;
	index++;
	int search_key = ASCII_TO_INT(query);
	if((query[index] =='g' && query[index+1] == 't') || (query[index] =='G' && query[index+1] == 'T'))
	{
		int details_key=0;
		if(operator_key == 3)
		{
			while(details_key<no_of_records)
			{
				if(search_key>details[details_key].marks)
				{
					break;
				}
				else if(search_key<=details[details_key].marks)
				{
					result_set->marks = details[details_key].marks;
					result_set->roll_no = details[details_key].roll_no;
					int iter_loop = 0;
					for(iter_loop=0;details[details_key].address[iter_loop]!='\0';iter_loop++)
					{
						result_set->address[iter_loop] = details[details_key].address[iter_loop];
					}
					result_set->address[iter_loop] = details[details_key].address[iter_loop];
					for(iter_loop=0;details[details_key].name[iter_loop]!='\0';iter_loop++)
					{
						result_set->name[iter_loop] = details[details_key].name[iter_loop];
					}
					result_set->name[iter_loop] = details[details_key].name[iter_loop];
					record_found++;
				}
				details_key++;
			}
		}
		else if(operator_key == 4)
		{
			while(details_key<no_of_records)
			{
				if(search_key>details[details_key].roll_no)
				{
					break;
				}
				else if(search_key<=details[details_key].roll_no)
				{
					result_set->marks = details[details_key].marks;
					result_set->roll_no = details[details_key].roll_no;
					int iter_loop = 0;
					for(iter_loop=0;details[details_key].address[iter_loop]!='\0';iter_loop++)
					{
						result_set->address[iter_loop] = details[details_key].address[iter_loop];
					}
					result_set->address[iter_loop] = details[details_key].address[iter_loop];
					for(iter_loop=0;details[details_key].name[iter_loop]!='\0';iter_loop++)
					{
						result_set->name[iter_loop] = details[details_key].name[iter_loop];
					}
					result_set->name[iter_loop] = details[details_key].name[iter_loop];
					record_found++;
				}
				details_key++;
			}
		}
	}
	else if((query[index] =='l' && query[index+1] == 'w') || (query[index] =='L' && query[index+1] == 'W'))
	{
		int details_key=0;
		if(operator_key == 3)
		{
			while(details_key<no_of_records)
			{
				if(search_key<details[details_key].marks)
				{
					break;
				}
				else if(search_key>details[details_key].marks)
				{
					result_set->marks = details[details_key].marks;
					result_set->roll_no = details[details_key].roll_no;
					int iter_loop = 0;
					for(iter_loop=0;details[details_key].address[iter_loop]!='\0';iter_loop++)
					{
						result_set->address[iter_loop] = details[details_key].address[iter_loop];
					}
					result_set->address[iter_loop] = details[details_key].address[iter_loop];
					for(iter_loop=0;details[details_key].name[iter_loop]!='\0';iter_loop++)
					{
						result_set->name[iter_loop] = details[details_key].name[iter_loop];
					}
					result_set->name[iter_loop] = details[details_key].name[iter_loop];
					record_found++;
				}
				details_key++;
			}
		}
		else if(operator_key == 4)
		{
			while(details_key<no_of_records)
			{
				if(search_key<details[details_key].roll_no)
				{
					break;
				}
				else if(search_key>details[details_key].roll_no)
				{
					result_set->marks = details[details_key].marks;
					result_set->roll_no = details[details_key].roll_no;
					int iter_loop = 0;
					for(iter_loop=0;details[details_key].address[iter_loop]!='\0';iter_loop++)
					{
						result_set->address[iter_loop] = details[details_key].address[iter_loop];
					}
					result_set->address[iter_loop] = details[details_key].address[iter_loop];
					for(iter_loop=0;details[details_key].name[iter_loop]!='\0';iter_loop++)
					{
						result_set->name[iter_loop] = details[details_key].name[iter_loop];
					}
					result_set->name[iter_loop] = details[details_key].name[iter_loop];

					*result_set_index = *result_set_index + 1;
					record_found++;
				}
				details_key++;
			}
		}
		
	}
	else if((query[index] =='e' && query[index+1] == 't') || (query[index] =='E' && query[index+1] == 'T'))
	{
		int details_key=0;
		if(operator_key == 3)
		{
			while(details_key!=no_of_records)
			{
				if(search_key<details[details_key].marks)
				{
					break;
				}
				else if(search_key==details[details_key].marks)
				{
					result_set->marks = details[details_key].marks;
					result_set->roll_no = details[details_key].roll_no;
					int iter_loop = 0;
					for(iter_loop=0;details[details_key].address[iter_loop]!='\0';iter_loop++)
					{
						result_set->address[iter_loop] = details[details_key].address[iter_loop];
					}
					result_set->address[iter_loop] = details[details_key].address[iter_loop];
					for(iter_loop=0;details[details_key].name[iter_loop]!='\0';iter_loop++)
					{
						result_set->name[iter_loop] = details[details_key].name[iter_loop];
					}
					result_set->name[iter_loop] = details[details_key].name[iter_loop];

					record_found++;
				}
				details_key++;
			}
		}
		else if(operator_key == 4)
		{
			while(details_key!=no_of_records)
			{
				if(search_key<details[details_key].roll_no)
				{
					break;
				}
				else if(search_key==details[details_key].roll_no)
				{
					result_set->marks = details[details_key].marks;
					result_set->roll_no = details[details_key].roll_no;
					int iter_loop = 0;
					for(iter_loop=0;details[details_key].address[iter_loop]!='\0';iter_loop++)
					{
						result_set->address[iter_loop] = details[details_key].address[iter_loop];
					}
					result_set[*result_set_index].address[iter_loop] = details[details_key].address[iter_loop];
					for(iter_loop=0;details[details_key].name[iter_loop]!='\0';iter_loop++)
					{
						result_set->name[iter_loop] = details[details_key].name[iter_loop];
					}
					result_set->name[iter_loop] = details[details_key].name[iter_loop];
					record_found++;
				}
				details_key++;
			}
		}
	}
	return result_set;
}

int classify_operator(char *buffer)
{
	char *operators[5] = {"name","address","marks","roll_no"};
	char *OPERATORS[5] = {"NAME","ADDRESS","MARKS","ROLL_NO"};
	int index = 0;
	while(index<4)
	{
		if((string_compare(buffer, operators[index]))==1 || string_compare(buffer, OPERATORS[index])==1)
		{
			return index+1;
		}
		if((string_compare(buffer, operators[index+1]))==1 || string_compare(buffer, OPERATORS[index+1])==1)
		{
			return index+2;
		}
		index+=2;
	}
	return -1;
}

RECORD classify_processing(char *query, RECORD *details, int  no_of_records)
{
	RECORD result_set = (RECORD*)malloc(sizeof(RECORD));
	int index = 0, token_index=0;
	char *token = (char*)calloc(1,sizeof(char));
	while(query[index]!='\0' && query[index]!=' ')
	{
		while(query[index]!='\0' && query[index]!=' ')
		{
			token = (char*)realloc(token,((index+2)*sizeof(char)));
			token[token_index] = query[index];
			index++;
			token_index++;
			token[token_index] = '\0';
		}
		int classification = classify_operator(token);
		if(classification <3)
		{
			result_set = string_query_processing(details, classification, query, index, no_of_records, result_set);
		}
		else if(classification>=3)
		{
			result_set = numeric_query_processing(details, classification, query, index, no_of_records, result_set);
		}
	}
	free(query);
	return result_set;
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fp = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\FILES SYTEM DATABASE\\FILES SYTEM DATABASE\\dbFile.db","rb+");
	RECORD *result_set = (RECORD*)malloc(1*sizeof(RECORD));
	int iter_loop = SIZE_OF_RECORD;
	printf("ENTER A QUERY: ");
	char *query  = (char*)calloc(1024,sizeof(char));
	gets(query);
	int no_of_records = NO_OF_RECORDS;
	while(iter_loop==SIZE_OF_RECORD)
	{
		printf("ITER LOOP: %d\n",iter_loop);
		RECORD *details = (RECORD*)malloc(iter_loop*sizeof(RECORD));
		fread(details,sizeof(RECORD),iter_loop,fp);
		result_set = classify_processing(query,details,iter_loop,result_set, &result_set_index);
		if(no_of_records - iter_loop > SIZE_OF_RECORD)
		{
			no_of_records-= iter_loop;
			free(details);
			continue;
		}
		else if(!(no_of_records - iter_loop > SIZE_OF_RECORD))
		{
			free(details);
			break;
		}
	}
	iter_loop = no_of_records - iter_loop;
	printf("ITER LOOP: %d\n",iter_loop);
	RECORD *details = (RECORD*)malloc(iter_loop*sizeof(RECORD));
	fread(details,sizeof(RECORD),iter_loop,fp);
	result_set = classify_processing(query,details,iter_loop,result_set, &result_set_index);
	for(int iter_loop=0;iter_loop<result_set_index;iter_loop++)
	{
		print_record(result_set[iter_loop]);
	}
	getchar();
	return 0;
}