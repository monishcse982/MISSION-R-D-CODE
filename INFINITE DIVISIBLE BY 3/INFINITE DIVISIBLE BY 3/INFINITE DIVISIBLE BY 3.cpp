// INFINITE DIVISIBLE BY 3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	printf("GIVE -1 TO STOP.\n");
	int odd=0, even=0;
	int read_int, count=1;
	scanf_s("%d",&read_int);
	while(read_int!=-1)
	{
		if(read_int<0 || read_int>1)
		{
			printf("INVALID INPUT");
			break;
		}
		if(count%2!=0 && read_int==1)
		{
			odd++;
		}
		else if(count%2==0 && read_int==1)
		{
			even++;
		}
		if((even-odd)%3==0)
		{
			printf("DIVISIBLE\n");
		}
		else if((even-odd)%3!=0)
		{
			printf("NOT DIVISIBLE.\n");
		}
		count++;
		scanf_s("%d",&read_int);
	}
	getchar();
	return 0;
}