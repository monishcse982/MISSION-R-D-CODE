// FILE SYSTEM 8MB HARD DRIVE.cpp : A file system implementation with a 8MB file.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "io.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#define SIZE 4194304

struct BLOCK_RECORD
{
	char file_name[20];
	int start_address;
	int size_in_bytes;
	int creation_time_in_epoch_int;
};

struct META_DATA
{
	BLOCK_RECORD file_entries[128];
	int links[2048];
	char bit_vector[2048];
	char wasteage[2048];
}MD;

FILE* create_file(char *filename)
{
	FILE *fp = fopen(filename,"wb");
	fclose(fp);
	return fp;
}

FILE* file_open(char *filename)
{
	FILE *fp = fopen(filename,"rb+");
	return fp;
}

void close_file(FILE *fp)
{
	fclose(fp);
}

FILE* My_create_disk( char *file_name)			//CREATES A FILE WITH SPECIFIED NAME AND SIZE AND WRITES IT WITH NULL CHARACTER.
{
	FILE *fp;
	fp = fopen(file_name,"wb");
	fseek(fp, SIZE, SEEK_SET);
	int iter_loop=0;
	while(iter_loop<SIZE)
	{
		putc('0', fp);
		iter_loop++;
	}
	rewind(fp);
	memset(MD.bit_vector,'0',2048);
	memset(MD.file_entries,'\0',128);
	for(int iter_loop=0;iter_loop<4;iter_loop++)
	{
		MD.bit_vector[iter_loop] = 1;
	}
	fwrite(&MD,sizeof(META_DATA),1,fp);
	return fp;
}

int epoch_to_int()
{
	time_t result;
    result = time(NULL);
	return result;
}

void my_write(FILE *fp, char *file_name, char *buffer_size)
{
	fwrite(file_name,1,strlen(file_name),fp);
}

BLOCK_RECORD* read_record(FILE* fp, char *file_name, int start_address, int file_size)
{
	char buffer[1024];
	BLOCK_RECORD *record = (BLOCK_RECORD*)malloc(sizeof(BLOCK_RECORD));
	strcpy(record->file_name,buffer);
	record->start_address = start_address;
	record->size_in_bytes = file_size;
	record->creation_time_in_epoch_int = epoch_to_int();
	fwrite(record,sizeof(BLOCK_RECORD),1,fp);
	return record;
}

//void update_bit_vector(FILE *fp,int bit_vector)
//{
//	int index;
//	char buffer[8];
//	int bit_vector[128];
//	FILE *temp = fp;
//	fread(&buffer,sizeof(buffer),1,temp);
//	fread(&index,sizeof(int),1,temp);
//	fwrite(&bit_vector,sizeof(bit_vector),1,fp);
//}

int compare_strings(char *string1, char *string2)
{
	for(int iter_loop=0;string1[iter_loop]!='\0' && string2[iter_loop]!='\0';iter_loop++)
	{
		if(string1[iter_loop] != string2[iter_loop])
		{
			return -1;
		}
	}
	return 1;
}

int get_free_block()
{
	for(int iter_loop=0;MD.bit_vector[iter_loop]!='\0';iter_loop++)
	{
		if(MD.bit_vector[iter_loop] == '0')
		{
			return iter_loop;
		}
	}
}

//BLOCK_RECORD* search_file(FILE* fp, char *search_key)
//{
//	BLOCK_RECORD *record = (BLOCK_RECORD*)malloc(sizeof(BLOCK_RECORD));
//	char *bit_vector = get_bit_vector(fp);
//	for(int iter_loop=5;iter_loop<120;iter_loop++)
//	{
//		fseek(fp, iter_loop*32, SEEK_SET);
//		fread(&record,sizeof(record),1,fp);
//		if(compare_strings(bit_vector[iter_loop],"1"))
//		{
//			if(compare_strings(record->file_name,search_key)==1)
//			{
//				return record;
//			}
//		}
//		
//	}
//	return NULL;
//}

void copy_data_to_MD(int index, BLOCK_RECORD *record)
{
	int iter_loop=0;
	while(record->file_name[iter_loop]!='\0')
	{
		MD.file_entries[index].file_name[iter_loop] = record->file_name[iter_loop];
		iter_loop++;
	}
	MD.file_entries[index].file_name[iter_loop] = '\0';
	MD.file_entries[index].size_in_bytes = record->size_in_bytes;
	MD.file_entries[index].start_address = record->start_address;
	MD.file_entries[index].creation_time_in_epoch_int = record->creation_time_in_epoch_int;
}



int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fp=NULL;
	int index=0;
	if(_access("MY_HARD_DRIVE.txt",0)==-1)
	{
		
		fp = My_create_disk("MY_HARD_DRIVE.txt");
	}
	else if(_access("MY_HARD_DRIVE.txt",0)!=-1)
	{
		char buffer[8];
		fp = file_open("MY_HARD_DRIVE.txt");
	}
	index = 5;
	get_meta_data(fp);
	close_file(fp);
	getchar();
	return 0;
}