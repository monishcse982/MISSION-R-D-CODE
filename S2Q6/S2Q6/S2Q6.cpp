// S2Q6.cpp : Given a two dimensional array, print the array on the console using '-'s and '|'s so that the output is displayed as a box. this is purely print based function so no test stubs needed
//

#include "stdafx.h"
#include "stdlib.h"

void print_array_in_a_box(int **input_array, int no_of_rows, int no_of_columns)
{
	int iter_loop=0,iter_loop2;;
	while(iter_loop<no_of_columns)               //LOOP TO PRINT THE TOP LINE
	{
		printf("---");
		iter_loop++;
	}

	printf("\n");
	iter_loop = 0;
	while(iter_loop<no_of_rows)                                       
	{
		iter_loop2 = 0;
		while(iter_loop2<no_of_columns)
		{
			if(iter_loop2 == 0)
			{
				printf("|");
			}
			printf("%d|",input_array[iter_loop][iter_loop2]);
			iter_loop2++;
		}
		if(iter_loop<no_of_rows-1)
		{
			printf("\n");
			iter_loop2 = 0;
			while(iter_loop2<no_of_columns)
			{
				printf("---");
				iter_loop2++;
			}
	}

		printf("\n");
		iter_loop++;
	}

	iter_loop = 0;
	while(iter_loop<no_of_columns)               //LOOP TO PRINT THE BOTTOM LINE
	{
		printf("---");
		iter_loop++;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int input_array[4][4] = {{11,22,33,44},{11,22,33,44},{11,22,33,44},{11,22,33,44}};
	int size_of_input[1][2] = {{4,4}};
	int iter_loop, iter_loop2,iter_loop3;

	for(iter_loop=0;iter_loop<1;iter_loop++)                                                  //CREATING THE DYNAMIC ARRAY.
	{
		int **input_matrix = (int**)calloc(size_of_input[iter_loop][0],sizeof(int*));

		for(iter_loop2=0;iter_loop2<size_of_input[iter_loop][1];iter_loop2++)
		{
			input_matrix[iter_loop2] = (int*)calloc(size_of_input[iter_loop][1],sizeof(int*));
		}

		for(iter_loop2=0;iter_loop2<size_of_input[iter_loop][0];iter_loop2++)                //COPYING DATA FROM STATIC ARRAY TO DYNAMIC ARRAY.
		{
			for(iter_loop3=0;iter_loop3<size_of_input[iter_loop][1];iter_loop3++)
			{
				input_matrix[iter_loop2][iter_loop3] = input_array[iter_loop2][iter_loop3];
			}
		}

		print_array_in_a_box(input_matrix,size_of_input[iter_loop][0],size_of_input[iter_loop][1]);

		for(iter_loop2=0;iter_loop2<size_of_input[iter_loop][0];iter_loop2++)                //DEALLOCATE MEMORY TO THE DYNAMIC ARRAY.
		{
			free(input_matrix[iter_loop2]);
		}
		free(input_matrix);
	}
	getchar();
	return 0;
}