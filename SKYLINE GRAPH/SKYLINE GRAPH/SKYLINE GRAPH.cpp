// SKYLINE GRAPH.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"

int** create_matrix(int *x_value, int *y_values, int x_max, int y_max)
{
	int** rows = (int**)calloc(x_max, sizeof(int));
	for(int iter_loop=0;iter_loop<x_max;iter_loop++)
	{
		rows[iter_loop] = (int*)calloc(y_max,sizeof(int));
	}

}

void read_inputs()
{
	int no_of_buildings;
	printf("ENTER THE NO OF BUILDINGS:");
	scanf("%d",&no_of_buildings);
	int *x_values = (int*)calloc((no_of_buildings*2),sizeof(int));
	int *y_values = (int*)calloc((no_of_buildings*2),sizeof(int));
	int y_max=-1, x_max=-1;
	for(int iter_loop=0;iter_loop<no_of_buildings;iter_loop++)
	{
		printf("X1 CO-ORDINATE: ");
		scanf("%d",x_values[iter_loop]);
		if(x_max<x_values[iter_loop])
		{
			x_max = x_values[iter_loop];
		}
		printf("Y1 CO-ORDINATE: ");
		scanf("%d",y_values[iter_loop]);
		if(y_max<x_values[iter_loop])
		{
			y_max = y_values[iter_loop];
		}
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

