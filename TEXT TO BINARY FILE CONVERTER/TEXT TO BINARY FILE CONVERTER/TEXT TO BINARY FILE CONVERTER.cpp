// TEXT TO BINARY FILE CONVERTER.cpp : Converter for text to binary conversion with tab seperated fields.
//
//Thaddeus	1509	80	Ap #154-1857 Nec Rd.
//Blair	9633	37	6233 A Rd.
//Stacey	9596	61	669 Condimentum. Av.
//This is the sample data.

#include "stdafx.h"
#include "stdlib.h"

struct RECORD
{
	char name[20];
	int roll_no;
	int age;
	char address[100];
};

void convert_text_file_to_bin_file(FILE *text, FILE *binary)
{
	RECORD *details = (RECORD*)malloc(1*sizeof(RECORD));
	int detatils_index = 0;
	if(fgetc(text)==EOF)
	{
		return;
	}
	while(fgetc(text)!=EOF)
	{
		fseek(text, ftell(text)-1,SEEK_CUR);
		details = (RECORD*)realloc(details,(detatils_index+2)*sizeof(RECORD));
		char ch = fgetc(text);
		while(ch!='\t' || ch!=EOF)
		{

		}

	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fp = fopen("D:\DATA TO BINARY FILE.txt","r+");
	FILE *bin_file = fopen("D:\BINARY FILE.bin","rb+");
	return 0;
}

