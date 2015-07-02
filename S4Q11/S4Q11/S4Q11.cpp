// S4Q11.cpp :  Factorial
//

#include "stdafx.h"

int factorial_one_way_recursion(int input)
{
	if(input==0)
	{
		return 1;
	}
	if(input<0)
	{
		printf("INVALID INPUT.");
		return -1;
	}
	if(input==0)
	{
		return 1;
	}
	else if(input>0)
	{
		return input*factorial_one_way_recursion(input-1);
	}
}

int factorial_two_way_recursion(int low, int high)
{
	if(high==0)
	{
		return 1;
	}
	else if(low>high)
	{
		printf("INVALID INPUT.");
		return -1;
	}
	else if(low==high && high==1)
	{
		return 1;
	}
	else if(low==high && low>1)
	{
		return low;
	}
	else if(low<high)
	{
		return (factorial_two_way_recursion(low,((low+high)/2)) * factorial_two_way_recursion(((low+high)/2)+1,high));
	}
}

void test_factorial()
{
	int input[7] = {0,1,5,10,-1,3};
	int output[7] = {1,1,120,3628800,-1,6};
	int iter_loop;
	for(iter_loop=0;iter_loop<6;iter_loop++)
	{
		(output[iter_loop]==factorial_one_way_recursion(input[iter_loop]))?printf("ACCEPTED : "):printf("REJECTED : ");
		(output[iter_loop]==factorial_two_way_recursion(1,input[iter_loop]))?printf("ACCEPTED\n"):printf("REJECTED\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_factorial();
	getchar();
	return 0;
}