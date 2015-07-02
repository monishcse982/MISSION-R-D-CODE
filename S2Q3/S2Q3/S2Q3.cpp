// S2Q3.cpp : Given a two dimensional matrix as input, write program to compute the transpose of the matrix. input array should be allocated dynamically, not statically as "int a [3][4]"
//

#include "stdafx.h"
#include "stdlib.h"

void transpose(int** input_array, int no_of_rows, int no_of_columns)
{
	int iter_row = 0, iter_column = 0, temp;
	while(iter_row<no_of_rows)
	{
		iter_column = iter_row + 1;
		while(iter_column<no_of_columns)
		{
			temp = input_array[iter_row][iter_column];
			input_array[iter_row][iter_column] = input_array[iter_column][iter_row];
			input_array[iter_column][iter_row] = temp;
			iter_column++;
		}
		iter_row++;
	}
}

int max(int num1, int num2)
{
	if(num1>num2)
	{
		return num1;
	}
	else if(num2>num1)
	{
		return num2;
	}
}

void test_transpose()
{
	int output_array[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	int input_array[4][3] = {{1,5,9},{2,6,10},{3,7,11},{4,8,12}};
	int rows_columns[1][2] = {{4,3}};
	int no_of_inputs=1;
	int iter_rows,iter_columns,iter_assign_rows,iter_assign_columns;
	int if_transpose = 1;

	for(iter_assign_rows=0;iter_assign_rows<no_of_inputs;iter_assign_rows++)
	{
		int **input_matrix = (int**)calloc(1+max(rows_columns[iter_assign_rows][0],rows_columns[iter_assign_rows][1]),sizeof(int*));
		for(iter_assign_columns=0;iter_assign_columns<1+max(rows_columns[iter_assign_rows][0],rows_columns[iter_assign_rows][1]);iter_assign_columns++)
		{
			input_matrix[iter_assign_columns] = (int*)calloc(1+max(rows_columns[iter_assign_rows][0],rows_columns[iter_assign_rows][1]),sizeof(int));
		}

		for(iter_rows=0;iter_rows<rows_columns[iter_assign_rows][0];iter_rows++)
		{
			for(iter_columns=0;iter_columns<rows_columns[iter_assign_rows][1];iter_columns++)
			{
				input_matrix[iter_rows][iter_columns] = input_array[iter_rows][iter_columns];
			}
		}

transpose(input_matrix, max(rows_columns[iter_assign_rows][0],rows_columns[iter_assign_rows][1]),max(rows_columns[iter_assign_rows][0],rows_columns[iter_assign_rows][1]));

		for(iter_rows=0;iter_rows<rows_columns[0][1];iter_rows++)
		{
			for(iter_columns=0;iter_columns<rows_columns[0][0];iter_columns++)
			{
				if(input_matrix[iter_rows][iter_columns] == output_array[iter_rows][iter_columns])
				{
					continue;
				}
				if(input_matrix[iter_rows][iter_columns] != output_array[iter_rows][iter_columns])
				{
					if_transpose--;
					break;
				}
			}
		}

		if(if_transpose == 1)
		{
			printf("ACCEPTED\n");
		}
		else if(if_transpose == 0)
		{
			if_transpose++;
			printf("REJECTTED\n");
		}


		for(iter_columns=0;iter_columns<max(rows_columns[iter_assign_rows][0],rows_columns[iter_assign_rows][1]);iter_columns++)
		{
			free(input_matrix[iter_columns]);
		}
		free(input_matrix);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_transpose();
	getchar();
	return 0;
}