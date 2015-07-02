// REVERSE ARRAY TESTING.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int arr[5] = {4,3,2,1};
	int i,j;
	for(i=0,j=4;i<=j;i++,j--)
	{
		arr[i] = arr[i] + arr[j];
		arr[j] = arr[i] - arr[j];
		arr[i] = arr[i] -arr[j];
	}
	for(i=0;i<4;i++)
	{
		printf("%d\t",arr[i]);
	}
	getchar();
	return 0;
}

