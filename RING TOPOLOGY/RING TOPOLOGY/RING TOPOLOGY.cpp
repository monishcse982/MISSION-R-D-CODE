// RING TOPOLOGY.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "string.h"
#include "stdlib.h"

int assign_ip(FILE *ip_t)
{
	int ip_address=0;
	printf("ASSIGN AN IP ADDRESS: ");
	scanf("%d",&ip_address);
	if(fgetc(ip_t)==EOF)
	{
		fprintf(ip_t,":%d\n",ip_address);
		fflush(ip_t);
		return ip_address;
	}
	rewind(ip_t);
	int existing_ip = 0;
	while(fgetc(ip_t)!=EOF)
	{
		fscanf(ip_t,"%d",&existing_ip);
		if(existing_ip == ip_address)
		{
			printf("INVALID IP ADDRESS, PLEASE ENTER A NEW ADDRESS: ");
			scanf("%d",&ip_address);
			rewind(ip_t);
			continue;
		}
		fscanf(ip_t,"%d:",&existing_ip);
	}
	fprintf(ip_t,":%d",ip_address);
	fflush(ip_t);
	return ip_address;
}

int validate_ip_address(int ip_adress, FILE *ip_table)
{
	int current_address = ftell(ip_table);
	rewind(ip_table);
	int existing_id;
	fscanf(ip_table,"%d",&existing_id);
	while (fgetc(ip_table)!=EOF)
	{
		if(existing_id == ip_adress)
		{
			fseek(ip_table,current_address,SEEK_SET);
			return 1;
		}
		else if(existing_id != ip_adress)
		{
			fscanf(ip_table,"%d",&existing_id);
		}
	}
	return -1;
}

//void check_connection_requests(int ip_address, FILE *control_table)
//{
//	int current_address = ftell(ip_table);
//	rewind(ip_table);
//	int existing_id;
//	fscanf(ip_table,"%d",&existing_id);
//	while (fgetc(ip_table)!=EOF)
//	{
//		if(existing_id == ip_adress)
//		{
//			return 1;
//		}
//		else if(existing_id != ip_adress)
//		{
//			fscanf(ip_table,"%d",&existing_id);
//		}
//	}
//	return -1;
//}

void check_for_messages(int ip_address,FILE *ip_table, FILE *control_table, FILE *data_file)
{
	int status=0;
	char ch = '\0';
	rewind(data_file);
	if(fgetc(data_file)==EOF)
	{
		printf("\nNO MESSAGES\n");
	}
	int current_address = ftell(data_file);
	rewind(data_file);
	int existing_id;
	fscanf(data_file,"%d",&existing_id);
	while (ch!=EOF)
	{
		if(existing_id == ip_address)
		{
			ch = fgetc(data_file);
			fscanf(data_file,"%d",&existing_id);
			int ack;
			ch = fgetc(data_file);
			fscanf(data_file,"%d",&ack);
			if(ack==1)
			{
				status++;
				fseek(data_file,ftell(data_file)-sizeof(char),SEEK_SET);
				fprintf(data_file,"%d",2);
				fflush(data_file);
				printf("%d SAID ",existing_id);
				ch = fgetc(data_file);
				char *buffer = (char*)calloc(1024,sizeof(char));
				fscanf(data_file,"%d",&existing_id);
				ch = fgetc(data_file);
				while(ch!=EOF && ch!='\n')
				{
					printf("%c",ch);
					ch = fgetc(data_file);
				}
				printf("\n");
			}
			fscanf(data_file,"%d",&existing_id);
		}
		else if(existing_id != ip_address)
		{
			char c = fgetc(data_file);
			while(c!='\n' && c!=EOF)
			{
				c = fgetc(data_file);
			}
			fscanf(data_file,"%d",&existing_id);
		}
		ch = fgetc(data_file);
		if(ch!=EOF)
		{
			fseek(data_file,ftell(data_file)-1,SEEK_SET);
		}
	}
	fseek(data_file,current_address,SEEK_SET);
	if(status==0)
	{
		printf("NO NEW MESSAGES!!!\n");
	}
}

void start_communication(int node_ip,FILE *ip_table, FILE *control_table, FILE *data_file)
{
	char *message = (char*)calloc(1024,sizeof(char));
	printf("ENTER AN IP ADDRESS FOR COMMUNICATION: ");
	int ip_address;
	scanf("%d",&ip_address);
	if(validate_ip_address(ip_address, ip_table)==1)
	{
		fseek(data_file,0,SEEK_END);
		printf("ENTER MESSAGE:  ");
		fflush(stdin);
		gets(message);
		fprintf(data_file,"%d:%d:%d:%s\n",ip_address,node_ip,1,message);
		fflush(data_file);
	}
	else if(validate_ip_address(ip_address, ip_table)!=1)
	{
		printf("INVALID IP ADDRESS, PLEASE ENTER A VALID IP ADDRESS.\n");
		start_communication(node_ip, ip_table, control_table, data_file);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *data_table = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\RING TOPOLOGY FILES\\DATA TABLE.txt","r+");
	 
	FILE *control_table = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\RING TOPOLOGY FILES\\CONTROL TABLE.txt","r+");

	FILE *routing_table = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\RING TOPOLOGY FILES\\ROUTING TABLE.txt","r+");

	FILE *ip_table = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\RING TOPOLOGY FILES\\VALID IP TABLE.txt","r+");

	int ip_address = assign_ip(ip_table);

	rewind(ip_table);
	fseek(control_table,0,SEEK_END);
	int choice;
	printf("TO SEND MESSAGES ENTER 1\nTO CHECK FOR EXISTING MESSAGES ENTER 2\nENTER YOUR CHOICE: ");
	scanf("%d",&choice);
	if(choice==1)
	{
		start_communication(ip_address,ip_table,control_table,data_table);
	}
	else if(choice==2)
	{
		check_for_messages(ip_address,ip_table,control_table,data_table);
	}
	return 0;
}