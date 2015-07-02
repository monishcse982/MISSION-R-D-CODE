// MULTI CLIENT NETWORK.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "stdlib.h"
#include "winsock2.h"
#define FIELD_SIZE 128

void update_bit_vector(FILE *fp, int *vector)
{
	int iter_loop=0;
	int current_position = ftell(fp);
	rewind(fp);
	fseek(fp,sizeof(int)+sizeof(char),SEEK_SET);
	while(iter_loop<128)
	{
		fprintf(fp,"%d",vector[iter_loop]);
		fflush(fp);
	}
	fseek(fp,current_position,SEEK_SET);
}

void reply_to_syn(FILE *fp, int my_id)
{
	rewind(fp);
	fseek(fp,2*sizeof(int),SEEK_SET);
	fseek(fp,128*sizeof(int),SEEK_SET);
	int client_id=0;
	fscanf(fp,"%d",&client_id);
	if(client_id == my_id)
	{
		int current_position = ftell(fp);
		fseek(fp,0,SEEK_END);
		fprintf(fp,"%d:1",my_id);
		fseek(fp,current_position,SEEK_SET);
		char ch = fgetc(fp);
		while(ch!='\n' || ch!=EOF)
		{
			ch = fgetc(fp);
		}
	}
	else
	{
		char ch = fgetc(fp);
		while(ch!='\n' || ch!=EOF)
		{
			ch = fgetc(fp);
		}
	}
}

void start_data_transfer(FILE *data_file, int my_id)
{
	rewind(data_file);
	int client_id;
	fscanf(data_file,"%d",&client_id);
	while(client_id!=EOF)
	{
		if(client_id == my_id)
		{
			fgetc(data_file);
			fscanf(data_file,"%d",&client_id);
			char c = fgetc(data_file);
			while(c!=EOF && c!='\n')
			{
				printf("%c",c);
				c = fgetc(data_file);
			}
		}
		else
		{
			char c = fgetc(data_file);
			while(c!=EOF && c!='\n')
			{
				printf("%c",c);
				c = fgetc(data_file);
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int my_id = 0;
	printf("			***********CLIENT***********\n");
	FILE *fp = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\MULTI CLIENT NETWORK CONTROL FILE.txt","r+");
	FILE *data_file = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\MULTI CLIENT NERWORK DATA FILE.txt","r+");
	int *vector = (int*)calloc(128,sizeof(int));
	printf("ASSIGN CLIENT ID: ");
	scanf("%d",&my_id);
	char syn[4];
	printf("ENTER SYN FOR COMMUNICATION:");
	scanf("%s",syn);
	int client_id;
	printf("ENTER THE CLIENT YOU WISH TO COMMUNICATE: ");
	scanf("%d",&client_id);
	int current_position = ftell(fp);
	rewind(fp);
	int ch;
	fscanf(fp,"%d",&ch);
	while(ch!=EOF)
	{
		if(ch ==client_id)
		{
			
		}
		else 
		{
			fscanf(fp,"%d",&ch);
		}
	}
	vector[my_id-1] = 1;
	if(fgetc(fp) == EOF)
	{
		fprintf(fp,"%d\n",0);
		fflush(fp);
		int vector_index = 0;
		while (vector_index<128)
		{
			fprintf(fp,"%d",vector[vector_index]);
			fflush(fp);
		}
		fprintf(fp,"%d:%s",my_id,syn);
		fflush(fp);
	}
	else
	{
		update_bit_vector(fp,vector);
		fseek(fp,0,SEEK_END);
		fprintf(fp,"%d:%s",my_id,syn);
		fflush(fp);
	}
	return 0;
}