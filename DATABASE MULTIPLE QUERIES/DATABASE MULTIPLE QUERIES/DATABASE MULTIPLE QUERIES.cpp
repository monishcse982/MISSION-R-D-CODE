// DATABASE MULTIPLE QUERIES.cpp : Defines the entry point for the console application.
//


#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "stdlib.h"

struct NODE
{
	char quer[128];
	NODE *left;
	NODE *right;
};

char* get_query()
{
	char *query = (char*)malloc(1024*sizeof(char));
	printf("ENTER THE QUERY: ");
	gets(query);
	return query;
}

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
	int result=1, iter_loop;
	for(iter_loop=0;iter_loop<power;iter_loop++)
	{
		result *= base;
	}
	return result;
}

void print_record(STUDENTS details)
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

void string_query_processing(STUDENTS *details, int operator_key, char *query, int index, int no_of_records)
{
	int record_found = 0;
	index++;
	if((query[index] =='s' && query[index+1] == 'w') || (query[index] =='S' && query[index+1] == 'W'))
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
					record_found++;
					print_record(details[details_key]);
				}
				index = 0;
				details_key++;
			}
			if(record_found==0)
			{
				printf("RECORD NOT FOUND\n");
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
					record_found++;
					print_record(details[details_key]);
				}
				index = 0;
				details_key++;
			}
			if(record_found==0)
			{
				printf("RECORD NOT FOUND\n");
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
					record_found++;
					print_record(details[details_key]);
				}
				index = search_index;
				details_key++;
			}
			if(record_found==0)
			{
				printf("RECORD NOT FOUND\n");
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
					record_found++;
					print_record(details[details_key]);
				}
				index = search_index;
				details_key++;
			}
			if(record_found==0)
			{
				printf("RECORD NOT FOUND\n");
			}
			free(search_key);
		}
	}
}

void numeric_query_processing(STUDENTS *details, int operator_key, char *query, int index, int no_of_records)
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
					record_found++;
					print_record(details[details_key]);
				}
				details_key++;
			}
			if(record_found==0)
			{
				printf("RECORD NOT FOUND\n");
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
					record_found++;
					print_record(details[details_key]);
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
					record_found++;
					print_record(details[details_key]);
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
					record_found++;
					print_record(details[details_key]);
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
					record_found++;
					print_record(details[details_key]);
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
					record_found++;
					print_record(details[details_key]);
				}
				details_key++;
			}
		}
		
	}
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

void classify_processing(STUDENTS *details, int no_of_records)
{
	while (1)
	{
	printf("ENTER A QUERY: ");
	char *query  = (char*)calloc(1024,sizeof(char));
	gets(query);
	if(string_compare(query,"exit")==1)
	{
		free(query);
		return;
	}
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
			string_query_processing(details, classification, query, index, no_of_records);
		}
		else if(classification>=3)
		{
			numeric_query_processing(details, classification, query, index, no_of_records);
		}
	}
	free(query);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

