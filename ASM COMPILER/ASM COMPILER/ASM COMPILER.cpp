// ASM COMPILER.cpp : A COMPILER FOR ASSEMBLY LEVEL LANGUAGE.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "stdlib.h"
#include "io.h"
#include "string.h"

struct REGISTERS
{
	char reg_name[3];
	int re_value;
};

struct IDENTIFIERS
{
	char id_name[5];
	int id_size;
	int *location;
	int value;
};

int exponent(int base, int power)
{
	int result=1, iter_loop;
	for(iter_loop=0;iter_loop<power;iter_loop++)
	{
		result *= base;
	}
	return result;
}

int string_rep_of_number_integer(char* input_array, int start)
{
	if(input_array[start] == '0')
	{
		return 0;
	}
	int result_integer=0, iter_loop = start, negative_input_flag=0, power=0;

	if(input_array[start] == '-')
	{
		negative_input_flag++;
	}

	while (input_array[iter_loop]!='\0')
	{
		if(negative_input_flag == 1 && iter_loop==start)
		{
			break;
		}
		if(input_array[iter_loop]<'0' && input_array[iter_loop]>'9')
		{
			printf("INVALID INPUT\n");
			return 0;
		}
		result_integer += (input_array[iter_loop] & ('p'-'a')) * exponent(10,power);
		power++;
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

//int is_keyword(char *token, int *size, FILE *fp, int *sym_index, int *symbol_table_size, IDENTIFIERS *symbol_table)
//{
//	printf("%c",fgetc(fp));
//	rewind(fp);
//	int iter_loop=0;
//	if(*size==3 && token[*size-1] == ':' && ((token[*size-2]>='a' && token[*size-2]<='z') ||(token[*size-2]>='A' && token[*size-2]<='Z')))
//	{
//		symbol_table = (IDENTIFIERS*)realloc(symbol_table,(*symbol_table_size+1)*sizeof(IDENTIFIERS));
//		int iter_loop2=0;
//		while(token[iter_loop2+1]!='\0')
//		{
//			symbol_table[*sym_index].id_name[iter_loop2] = token[iter_loop2];
//			iter_loop2++;
//		}
//		symbol_table[*sym_index].id_size = 2;
//		symbol_table[*sym_index].id_value = -1;
//		symbol_table[*sym_index].location = ftell(fp)-*size;
//		*sym_index = *sym_index + 1;
//		*symbol_table_size = *symbol_table_size+1;
//		return 1;
//	}
//}

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

int add_to_symbol_table_CONST(char *buffer, IDENTIFIERS *symbol_table, int *symbol_table_size, int *sym_index)			//TAKES A LINE AND PUTS IT TO SYMBOL TABLE.
{
	int iter_loop=0;
	while(buffer[iter_loop] != ' ')
	{
		iter_loop++;
	}
	iter_loop++;
	char variable[5];
	int iter_loop2=0;
	while(buffer[iter_loop]!=' ')
	{
		variable[iter_loop2] = buffer[iter_loop];
		iter_loop++;
		iter_loop2++;
	}
	variable[iter_loop2] = '\0';
	iter_loop+=3;
	int value = string_rep_of_number_integer(buffer,iter_loop);
	iter_loop2 = 0;
	symbol_table = (IDENTIFIERS*)realloc(symbol_table,(sizeof(IDENTIFIERS)*(*symbol_table_size+1)));
	*symbol_table_size = *symbol_table_size+1;
	while(variable[iter_loop2]!='\0')
	{
		symbol_table[*sym_index].id_name[iter_loop2] = variable[iter_loop2];
		iter_loop2++;
	}
	symbol_table[*sym_index].id_size = 1;
	symbol_table[*sym_index].value = value;
	return 1;
}

int add_to_symbol_table_DATA(char *buffer, IDENTIFIERS *symbol_table, int *symbol_table_size, int *sym_index)			//TAKES A LINE AND PUTS IT TO SYMBOL TABLE.
{
	char *variable = (char*)malloc(1*sizeof(char));
	int size = 0;
	int array_flag = -1;
	int iter_loop=0;
	while(buffer[iter_loop]!=' ')
	{
		iter_loop++;		
	}
	iter_loop++;
	int iter_loop2=0;
	while(buffer[iter_loop]!='\0' &&  buffer[iter_loop]!='[')
	{
		if(buffer[iter_loop] == '[')
		{
			array_flag = iter_loop;
		}
		if(buffer[iter_loop-1]==' ' && ((buffer[iter_loop]<'A' && buffer[iter_loop]>'Z') || (buffer[iter_loop]<'a' && buffer[iter_loop]>'z')))
		{
			return -1;			
		}
		variable = (char*)realloc(variable,(size+1)*sizeof(char));
		variable[iter_loop2] = buffer[iter_loop];
		iter_loop2++;
		iter_loop++;
	}
	variable[iter_loop2] = '\0';
	if(string_length(variable)>4)
	{
		return -1;		
	}
	iter_loop=0;
	symbol_table = (IDENTIFIERS*)realloc(symbol_table,(sizeof(IDENTIFIERS)*(*symbol_table_size+1)));
	*symbol_table_size = *symbol_table_size+1;
	while(variable[iter_loop]!='\0')
	{
		symbol_table[*sym_index].id_name[iter_loop] = variable[iter_loop];
		iter_loop++;
	}
	if(array_flag==-1)
	{
		symbol_table[*sym_index].id_size = 1;
	}
	else if(array_flag !=-1)
	{
		symbol_table[*sym_index].id_size = string_rep_of_number_integer(variable,array_flag);
	}
	*sym_index = *sym_index+1;
	return 1;
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

void read_tokens(char *line,FILE *fp, IDENTIFIERS *symbol_table, int *symbol_table_size, int *sym_index)
{
	int iter_loop=0;
	int size=1;
	int index=0;
	while(line[iter_loop]!='\0')
	{
		char *buffer = (char*)malloc(1*sizeof(char));
		while(line[iter_loop]!=' ' && line[iter_loop]!='\n')
		{
			buffer = (char*)realloc(buffer,(++size)*sizeof(char));
			buffer[index] = line[iter_loop];
			index++;
			buffer[index] = '\0';
			iter_loop++;
		}
		printf("%s   ",buffer);
		int choice = classify_var(buffer);
		switch (choice)
		{
		case 1:
			add_to_symbol_table_DATA(line, symbol_table, symbol_table_size, sym_index);
			break;
		case 2:
			add_to_symbol_table_CONST(line, symbol_table, symbol_table_size, sym_index);
			break;

		default:
			break;
		}
		buffer = (char*)malloc(1*sizeof(char));
		index = 0;
		size=1;
		free(buffer);
		return;
	}
}

char* read_line(FILE *fp, char *line, int *line_size, int *sym_index, int *symbol_table_size, IDENTIFIERS *symbol_table)
{
	char ch = fgetc(fp);
	if(fp==NULL)
	{
		return NULL;
	}
	if((ch=='\n' && ch==EOF))
	{
		return NULL;
	}
	int index=0;
	while((ch!='\n' && ch!=EOF))
	{
		line = (char*)realloc(line,(*line_size+1)*sizeof(char));
		line[index] = ch;
		index++;
		*line_size = *line_size+1;
		ch = fgetc(fp);
	}
	line[index] = '\0';
	printf("%s\n\n",line);
	return line;
}

void lexical_analyzer(FILE *fp, IDENTIFIERS *symbol_table, int *symbol_table_size, int *sym_index)
{
	printf("%c",fgetc(fp));
	rewind(fp);
	char *line = (char*)malloc(1*sizeof(char));
	int size=1;
	line = read_line(fp, line, &size, sym_index, symbol_table_size, symbol_table);
	line[size] = '\0';
	while(line!=NULL)
	{
		read_tokens(line, fp, symbol_table, symbol_table_size, sym_index);
		memset(line,'\0',size);
		int size=1;
		line = read_line(fp, line, &size, sym_index, symbol_table_size, symbol_table);
		line[size] = '\0';
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("ENTER FILE NAME. THE FILE MUST BE A .asm FILE: ");
	char *file_name = (char*)malloc(20*sizeof(char));
	scanf("%s",file_name);
	REGISTERS *register_info = (REGISTERS*)malloc(10*sizeof(REGISTERS));
	FILE *src = fopen(file_name,"r");
	if(src ==  NULL)
	{
		printf("FILE NOT FOUND\n");
		getchar();
		return 0;
	}
	else if(src!=NULL)
	{
		printf("FILE FOUND\n");
		IDENTIFIERS *symbol_table = (IDENTIFIERS*)malloc(1*sizeof(IDENTIFIERS));
		int  symbol_table_size = 1;
		int sym_index=0;
		char *key_words[18] = {"IF","THEN","ELSE","MOV","START", "END", "ADD", "SUB", "MUL","DATA","CONST","READ","PRINT","EQ","GT","LT","LE","GE"};
		char reg_names[9][3]= {"AX","BX","CX","DX","EX","FX","GX","HX","CR"};
		for(int iter_loop=0;iter_loop<=9;iter_loop++)
		{
			for(int iter_loop2=0;iter_loop2<3;iter_loop2++)
			{
				register_info[iter_loop].reg_name[iter_loop2] = reg_names[iter_loop][iter_loop2];
				register_info[iter_loop].re_value = 0;
			}
		}
		printf("%c",fgetc(src));
		rewind(src);
		lexical_analyzer(src,symbol_table,&symbol_table_size,&sym_index);
		free(register_info);
	}
	
	getchar();
	return 0;
}