// NETWORK SERVER.cpp : Defines the entry point for the console application.
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

int check_for_fin(FILE *fp)
{
	char c = fgetc(fp); 
	printf("%c",c);
	if(c != 'N' && c != 'n' )
	{
		return -1;
	}
	printf("\nCLIENT IS REQUESTING TO TERMINATE: ");
	char *message = (char*)calloc(1024,sizeof(char));
	gets(message);
	if((string_compare(message,"FINACK")==1) || (string_compare(message,"finack")==1))
	{
		fprintf(fp,"%s",message);
		fflush(fp);
		return 1;
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

void write_data_to_file(FILE *fp)
{
	printf("\nGIVE SYNC INFORMATION:  ");
	char *message = (char*)calloc(1024,sizeof(char));
	gets(message);
	while(string_compare(message,"STATUS")!=1 || string_compare(message,"status")!=1)
	{
		if(string_compare(message,"STATUS")==1 || string_compare			(message,"status")==1)
		{
			printf("CONNECTION IN PROGRESS....\n");
		}
		free(message);
		printf("\nGIVE SYNC INFORMATION:  ");
		gets(message);
	}
	fprintf(fp,"%s",message);
	fflush(fp);
	free(message);
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

int check_for_syn(FILE *fp)
{
	char syn_ack[3] = {'y','n'};
	char SYN_ACK[3] = {'Y','N'};
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

int check_for_ack(FILE *fp)
{
	char syn_ack[5] = {'c','k'};
	char SYN_ACK[5] = {'C','K'};
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

int three_way_handshake(FILE *fp)
{
	char c = busy_waiting(fp);
	char *reply = (char*)calloc(1,sizeof(char));
	if((c == 's' || c=='S') && (1==(check_for_stat(fp))))
	{
		write_data_to_file(fp);
	}
	if((c == 's' || c=='S') && (1==(check_for_syn(fp))))
	{
		write_data_to_file(fp);
	}
	else if((c=='s' || c=='S') &&(-1==(check_for_syn(fp))))
	{
		fprintf(fp,"%s","MONI");
		fflush(fp);
		return -1;
	}
	c = busy_waiting(fp);
	if((c!='a' || c!='A')&&(1==(check_for_ack(fp))))
	{
		return 1;
	}
	else if((c!='a' || c!='A')&&(1==(check_for_ack(fp))))
	{
		fprintf(fp,"%s","MONI");
		fflush(fp);
		return -1;
	}
	else if((c!='a' || c!='A'))
	{
		fprintf(fp,"%s","MONI");
		fflush(fp);
		return -1;
	}
}

int reach_end(FILE *fp)
{
	char c = fgetc(fp);
	printf("%c",c);
	if((c=='i' || c=='I') && check_for_fin(fp)==1)
	{
		return -1;
	}
	c = fgetc(fp);
	while(c!=EOF)
	{
		printf("%c",c);
		c = fgetc(fp);
	}
	printf("\n");
	return 1;
}

char write_message(FILE *fp)
{
	char *message = (char*)calloc(1024,sizeof(char));
	printf("SERVER: ");
	gets(message);
	fprintf(fp,"%s",message);
	free(message);
	fflush(fp);
	return busy_waiting(fp);
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fp = fopen("D:/MISSION R&D/C ONLINE COURSE/MESSAGE BUFFER.txt", "w");
	fclose(fp);
	fp = fopen("D:/MISSION R&D/C ONLINE COURSE/MESSAGE BUFFER.txt", "r+");
	if(three_way_handshake(fp) == -1)
	{
		printf("CONNECTION COULDN'T BE ESTABLISHED\n");
		return 0;
	}
	printf("CONNECTION ESTABLISHED\n");
	char reply;
	reply = busy_waiting(fp);
	while(reply!='$')
	{
		printf("CLIENT: ");
		printf("%c",reply);
		if (reach_end(fp)==-1)
		{
			return 0;
		}
		reply = write_message(fp);
	}
	fprintf(fp,"%c",'$');
	fclose(fp);
	return 0;
}