// NETWORK CLIENT.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "stdlib.h"
#include "string.h"

int string_compare(char *string1, char *string2)
{
	int iter_loop=0;
	while(string1[iter_loop]!='\0' && string2[iter_loop]!='\0')
	{
		if(string1[iter_loop] == string2[iter_loop])
		{
			return -1;
		}
		iter_loop++;
	}
	return 1;
}

int check_for_fin_ack(FILE *fp)
{
	char syn_ack[5] = {'n','a','c','k','\0'};
	char SYN_ACK[5] = {'N','A','C','K','\0'};
	char c = fgetc(fp);
	int iter_loop=0;
	while(syn_ack[iter_loop]!='\0')
	{
		if(syn_ack[iter_loop] != c && SYN_ACK[iter_loop] != c)
		{
			return -1;
		}
		c = fgetc(fp);
		iter_loop++;
	}
	if(syn_ack[iter_loop]!='\0')
	{
		return -1;
	}
	return 1;
}

int check_for_fin(FILE *fp)
{
	char syn_ack[3] = {'i','n','\0'};
	char SYN_ACK[3] = {'I','N','\0'};
	char c = fgetc(fp);
	int iter_loop=0;
	while(syn_ack[iter_loop]!='\0')
	{
		printf("%c",c);
		if(syn_ack[iter_loop] != c && SYN_ACK[iter_loop] != c)
		{
			return 1;
		}
		c = fgetc(fp);
		iter_loop++;
	}
	printf("SERVER IS REQUESTING TO TERMINATE: ");
	char *message = (char*)calloc(1024,sizeof(char));
	gets(message);
	if((string_compare(message,"FINACK")==1) || (string_compare(message,"finack")==1))
	{
		free(message);
		return -1;
	}
}

char busy_waiting(FILE *fp)
{
	char c = fgetc(fp);
	while(c ==  EOF && c !=' ')
	{
		c = fgetc(fp);
	}
	return c;
}

int check_for_stat(FILE *fp)
{
	char syn_ack[6] = {'t','a','t','u','s','\0'};
	char SYN_ACK[6] = {'T','A','T','U','S','\0'};
	char c = fgetc(fp);
	int iter_loop=0;
	while(syn_ack[iter_loop]!='\0')
	{
		if(syn_ack[iter_loop] != c && SYN_ACK[iter_loop] != c)
		{
			return -1;
		}
		c = fgetc(fp);
		iter_loop++;
	}
	if(syn_ack[iter_loop]=='\0')
	{
		printf("\nCONNECTION IN PROGRESS....\n");
		return 1;
	}
	else {return -1;}
}

int check_for_syn_ack(FILE *fp)
{
	char syn_ack[6] = {'y','n','a','c','k','\0'};
	char SYN_ACK[6] = {'Y','N','A','C','K','\0'};
	char c = fgetc(fp);
	int iter_loop=0;
	while(syn_ack[iter_loop]!='\0')
	{
		if(syn_ack[iter_loop] != c && SYN_ACK[iter_loop] != c)
		{
			fprintf(fp,"%s","MONI");
			fflush(fp);
			return -1;
		}
		c = fgetc(fp);
		iter_loop++;
	}
	return 1;
}

void write_data_to_file(FILE *fp)
{
	printf("\nGIVE SYNC INFORMATION:  ");
	char *message = (char*)calloc(1024,sizeof(char));
	gets(message);
	while(string_compare(message,"STATUS")==1 || string_compare			(message,"status")==1)
	{
		printf("CONNECTION IN PROGRESS....\n");
		printf("\nGIVE SYNC INFORMATION:  ");
		gets(message);
	}
	fprintf(fp,"%s",message);
	fflush(fp);
	free(message);
}

int three_way_handshake(FILE *fp)
{
	write_data_to_file(fp);
	char c = busy_waiting(fp);
	char *reply = (char*)calloc(1,sizeof(char));
	if((c == 's' || c=='S') && (1==(check_for_stat(fp))))
	{
		write_data_to_file(fp);
	}
	else if((c == 's' || c=='S') && (1==(check_for_syn_ack(fp))))
	{
		write_data_to_file(fp);
	}
	else if((c=='s' || c=='S') ||(-1==(check_for_syn_ack(fp))))
	{
		fprintf(fp,"%s","MONI");
		fflush(fp);
		return -1;
	}
	else if((c!='s' || c!='S'))
	{
		fprintf(fp,"%s","MONI");
		fflush(fp);
		return -1;
	}

}

int reach_end(FILE *fp)
{
	char c = fgetc(fp);
	if((c =='I' || c =='i') && (check_for_fin_ack(fp)==1))
	{
		return -1;
	}
	while(c!=EOF)
	{
		printf("%c",c);
		c = fgetc(fp);
	}
	printf("\n");
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fp = fopen("D:/MISSION R&D/C ONLINE COURSE/MESSAGE BUFFER.txt", "w");
	fclose(fp);
	printf("CLIENT: ");
	fp = fopen("D:/MISSION R&D/C ONLINE COURSE/MESSAGE BUFFER.txt", "r+");
	if(three_way_handshake(fp) == -1)
	{
		printf("CONNECTION COULDN'T BE ESTABLISHED\n");
		return 0;
	}
	printf("CONNECTION ESTABLISHED\n");
	char *message = (char*)calloc(1024,sizeof(char));
	char reply;
	gets(message);
	while(1)
	{
		fprintf(fp,"%s",message);
		fflush(fp);
		reply = busy_waiting(fp);
		if(reply == '$' && reply !=' ')
		{
			break;
		}
		printf("SERVER: ");
		printf("%c",reply);
		if(reach_end(fp)==-1)
		{
			printf("-----------hhhh------------\n");
			if((string_compare(message,"FIN")==1) || (string_compare(message,"fin")==1))
			{
				break;
			}
		}
		printf("CLIENT: ");
		gets(message);
	}
	free(message);
	fprintf(fp,"%c",'$');
	return 0;
}