// MAGIC 6 BIT NUMBER.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"


int check_if_magic_number(int num)
{
	int *table = (int*)calloc(10,sizeof(int));
	int sum = num*2;
	for(int i=0;i<6;i++)
	{
		table[sum%10] = sum%10;
		sum = sum/10;
	}
	for(int i=3;i<=6;i++)
	{
		int sum = num*i;
		for(int j=0;j<6;j++)
		{
			if(table[sum%10]==sum%10)
			{
				sum = sum/10;
				continue;
			}
			else if(table[sum%10]!=sum%10)
			{
				return -1;
			}
			sum = sum/10;
		}
	}
	free(table);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int num_array, *temp, result, iter_loop;
	for(int num= 100000;num<=999999;num++)
	{
		if(0 == check_if_magic_number(num))
		{
			printf("%d",num);
			break;
		}
	}
	getchar();
	return 0;
}