// COMPILER.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "stdlib.h"
#include "io.h"
#include "string.h"

struct SYMBOL_TABLE
{
	 char id_name[5];
	 int id_size;
	 int location;
	 SYMBOL_TABLE *NEXT;
};

struct INSTRUCTIONS
{
	int inst_id;
	int operand_1;
	int operand_2;
};

struct REGISTERS
{
	char reg_name[3];
	int reg_value;
};



int string_compare(char *string1, char *string2)
{
	int iter_loop=0;
	while(string1[iter_loop]!='\0' || string2[iter_loop]!='\0')
	{
		if(string1[iter_loop] != string2[iter_loop])
		{
			return -1;
		}
		iter_loop++;
	}
	return 1;
}

int string_length(char *string1)
{
	if(string1 == NULL)
	{
		return -1;
	}
	int iter_loop=0;
	while(string1[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop++;
}

int check_if_goto(char *buffer)
{
	if(buffer == NULL)
	{
		return -1;
	}
	int iter_loop=0;
	int length = string_length(buffer);
	if(length==3 && buffer[1]==':')
	{
		if((buffer[0]>='a' && buffer[0]<='z') || (buffer[0]>='A' && buffer[0]<='Z'))
		{
			return 1;
		}
	}
	return 0;
}

int classify_var(char *buffer)
{
	if(string_compare(buffer,"DATA")==1)
	{
		return 1;
	}
	else if(string_compare(buffer,"CONST")==1)
	{
		return 2;
	}
	else if(string_compare(buffer,"MOV")==1)
	{
		return 3;
	}
	else if(string_compare(buffer,"ADD")==1)
	{
		return 4;
	}
	else if(string_compare(buffer,"SUB")==1)
	{
		return 5;
	}
	else if(string_compare(buffer,"MUL")==1)
	{
		return 6;
	}
	else if(string_compare(buffer,"READ")==1)
	{
		return 7;
	}
	else if(string_compare(buffer,"PRINT")==1)
	{
		return 8;
	}
	else if(string_compare(buffer,"IF")==1)
	{
		return 9;
	}
	else if(string_compare(buffer,"ELSE")==1)
	{
		return 10;
	}
	else if(string_compare(buffer,"START")==1)
	{
		return 11;
	}
	else if(string_compare(buffer,"END")==1)
	{
		return 12;
	}
	else if(string_compare(buffer,"JMP")==1)
	{
		return 13;
	}
	else if(check_if_goto(buffer)==1)
	{
		return 14;
	}
}

void update_table_DATA(char *buffer, int **memory_space, int *memory_index, SYMBOL_TABLE *symbol_table, int *sym_index)
{
	int iter_loop=0;
	while(buffer[iter_loop]!='\0')
	{
		iter_loop++;
	}
	iter_loop++;
	char *variable = (char*)calloc(5,sizeof(5));
	variable[4] = '\0';
	int index=0;
	while (buffer[iter_loop]!=' ' && buffer[iter_loop]!='\0')
	{
		variable[index] = buffer[iter_loop];
		index++;
		iter_loop++;
	}
	variable[index] = '\0';
	symbol_table = realloc(symbol_table, (sym_index+1)*sizeof(SYMBOL_TABLE));
}

void get_token(char *line)
{
	printf("\n---------\nTOKENS\n---------\n");
	int iter_loop=0;
	char *token = (char*)malloc(sizeof(char));
	int index = 0;
	while(line[iter_loop]!='\0' && line[iter_loop-1]!='\0')
	{
		while(line[iter_loop]!=' ' && line[iter_loop]!='\0')
		{
			if(line[iter_loop]=='\n')
			{
				iter_loop++;
				continue;
			}
			token = (char*)realloc(token,(index+2)*sizeof(char));
			token[index] = line[iter_loop];
			index++;
			iter_loop++;
		}
		token[index] = '\0';
		printf("%s , ",token);
		memset(token,'\0',index);
		iter_loop++;
		index = 0;
	}
}

void get_line(FILE *src, int **memory_space, int *memory_index, SYMBOL_TABLE *symbol_table,int *sym_index)
{
	char *line = (char*)malloc(sizeof(char));
	int line_size = 0;
	char ch = fgetc(src);
	if(src==NULL)
	{
		return;
	}
	if((ch=='\n' && ch==EOF))
	{
		return;
	}
	int index=0;
	while((ch!='\n' && ch!=EOF))
		{
			line = (char*)realloc(line,(line_size+1)*sizeof(char));
			line[index] = ch;
			index++;
		line_size = line_size+1;
			ch = fgetc(src);
		}
		line[index] = '\0';
		printf("%s",line);
		get_token(line);
	while(ch!=EOF)
	{
		memset(line,'\0',line_size);
		line_size = 0;
		index = 0;
		do
		{
			line[index] = ch;
			index++;
		line_size = line_size+1;
			ch = fgetc(src);
		}while((ch!='\n' && ch!=EOF));
		line[index] = '\0';
		printf("%s",line);
		get_token(line);
	}
	getchar();
}

void driver_for_compiler()
{
	printf("ENTER FILE NAME. THE FILE MUST BE A .asm FILE: ");
		char *file_name = (char*)malloc(20*sizeof(char));
		scanf("%s",file_name);
		FILE *src = fopen(file_name,"r");
		if(src ==  NULL)
		{
			printf("FILE NOT FOUND\n");
			getchar();
			return;
		}
	REGISTERS  *register_info = (REGISTERS*)malloc(10*sizeof(REGISTERS));
	int iter_loop=0;
	char register_name[9][3]= {"AX","BX","CX","DX","EX","FX","GX","HX","CR"};
		for(int iter_loop=0;iter_loop<9;iter_loop++)
		{
			for(int iter_loop2=0;iter_loop2<3;iter_loop2++)
			{
				register_info[iter_loop].reg_name[iter_loop2] = register_name[iter_loop][iter_loop2];
				register_info[iter_loop].reg_value = 0;
			}
		}
		SYMBOL_TABLE  *symbol_table = (SYMBOL_TABLE*)malloc(sizeof(SYMBOL_TABLE));
		int sym_index = 0;
		int *memory_space = (int*)calloc(10000,sizeof(char));
		INSTRUCTIONS *inst_table = (INSTRUCTIONS*)malloc(1*sizeof(INSTRUCTIONS));
		int inst_num = 0;
		int free_memory_index = 0;
		get_line(src, &memory_space, &free_memory_index,symbol_table,&sym_index);
}

int _tmain(int argc, _TCHAR* argv[])
{
	driver_for_compiler();
	getchar();
	return 0;
}