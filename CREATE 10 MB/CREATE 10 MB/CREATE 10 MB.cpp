// CREATE 10 MB.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#define mb 1024*1024

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *file = fopen("D:\\MISSION R&D\\C ONLINE COURSE\\PROJECT FACEBOOK\\PROJECT FACEBOOK\\BlobText.txt","wb+");
	int iter_loop = 0;
	for(int i = 0 ; i < (10*mb)/2 ; i++)
	{
		fputc('0',file);
	}
	fclose(file);
	printf("DONE\a");
	return 0;
}