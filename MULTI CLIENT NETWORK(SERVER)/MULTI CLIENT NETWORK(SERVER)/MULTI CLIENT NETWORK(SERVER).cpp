// MULTI CLIENT NETWORK(SERVER).cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "stdlib.h"

char busy_waiting(FILE *fp)
{
	char c = fgetc(fp);
	while(c!=EOF)
	{
		c = fgetc(fp);
	}
	return c;
}



int _tmain(int argc, _TCHAR* argv[])
{
	printf("			***********SERVER***********\n");
	FILE *fp = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\MULTI CLIENT NERWORK DATA FILE.txt","r+");
	fseek(fp,ftell(fp),SEEK_SET);
	return 0;
}