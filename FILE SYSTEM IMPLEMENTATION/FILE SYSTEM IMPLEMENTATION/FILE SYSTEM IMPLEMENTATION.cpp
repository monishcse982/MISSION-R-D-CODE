// FILE SYSTEM IMPLEMENTATION.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "io.h"

FILE* format_disk(char *file_name)
{
	FILE *hard_drive = fopen(file_name,"rb+");
	fread();
}

int get_free_block_address(char *vector)
{
	for(int iter_loop=0;iter_loop<120;iter_loop++)
	{
		if(vector[iter_loop]=='0')
		{
			return iter_loop;
		}
	}
	return -1;
}

void write_index_vector_to_file(FILE *hard_drive, int index, char *vector)
{
	fseek(hard_drive,0,SEEK_SET);
	fwrite("FILES",sizeof("FILES"),1,hard_drive);
	fwrite(&index,sizeof(int),1,hard_drive);
	fwrite(&vector,sizeof(vector),1,hard_drive);
}

int get_data(FILE *hard_drive, int index, char *vector)
{
	while(1)
	{
		printf("1 CREATE NEW FILE 2. WRITE FILE 3. LIST FILES 4. SEARCH 5. DELETE FILES 6. IMPORT FILE 7. EXPORT\n 8. EXIT\nENTER CHOICE:  ");
		int choice;
		scanf("%d",&choice);
		switch (choice)
		{
		case 1:								//CREATE A NEW FILE AND SAVE.


		default:
			break;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *hard_drive;
	int index = 4;
	char vector[121];
	if(_access("MY_HARD_DRIVE.txt",0)!=-1)
	{
		hard_drive = fopen("MY_HARD_DRIVE.txt","rb+");
		fread("FILE",sizeof("FILES"),1,hard_drive);
		fread(&index,sizeof(index),1,hard_drive);
		fread(vector,sizeof(vector),1,hard_drive);
		rewind(hard_drive);
	}
	else if(_access("MY_HARD_DRIVE.txt",0)==-1)
	{
		memset(vector,0,121);
		hard_drive = fopen("MY_HARD_DRIVE.txt","wb+");
		fseek(hard_drive,(1024*1024*8)-1,SEEK_SET);
		memset(hard_drive,0,(1024*1024*8)-1);
		rewind(hard_drive);
	}
	get_data();
	return 0;
}