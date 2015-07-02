// S2Q10.cpp : Given a two dimensional character array and a word, check whether the word is present in the array as a continuous word row wise or column wise and diagonally downside (not upside). rowwise also left to right, column wise top to down. word cant be in two rows or columns it has to be in single row or column
//

#include "stdafx.h"
#include "stdlib.h"

int vertical(char **input_array, int x_axis, int y_axis, char* search_key, int rows, int columns)
{
	int iter_loop=x_axis,iter_loop2=0;
	while(iter_loop<rows && search_key[iter_loop2]!='\0')
	{
		if(input_array[iter_loop][y_axis] == search_key[iter_loop2])
		{
			iter_loop2++;
			iter_loop++;
			continue;
		}
		else if(input_array[iter_loop][y_axis] != search_key[iter_loop2])
		{
			return 0;
		}
	}
	if(search_key[iter_loop2]=='\0')
	{
		return 1;
	}
}

int horizontal(char **input_array, int x_axis, int y_axis, char* search_key, int rows, int columns)
{
	int iter_loop=y_axis,iter_loop2=0;
	while(iter_loop<columns && search_key[iter_loop2]!='\0')
	{
		if(input_array[x_axis][iter_loop] == search_key[iter_loop2])
		{
			iter_loop2++;
			iter_loop++;
			continue;
		}
		else if(input_array[x_axis][iter_loop] != search_key[iter_loop2])
		{
			return 0;
		}
	}
	if(search_key[iter_loop2]=='\0')
	{
		return 1;
	}
}

int parallel_to_primary_diagonal(char **input_array, int x_axis, int y_axis, char* search_key, int rows, int columns)
{
	int iter_loop=x_axis,iter_loop2=y_axis,iter_loop3=0;
	while((iter_loop<rows && iter_loop2<columns) && search_key[iter_loop3]!='\0')
	{
		if(input_array[iter_loop][iter_loop2] == search_key[iter_loop3])
		{
			iter_loop2++;
			iter_loop3++;
			iter_loop++;
			continue;
		}
		else if(input_array[iter_loop][iter_loop2] != search_key[iter_loop3])
		{
			return 0;
		}
	}
	if(search_key[iter_loop3]=='\0')
	{
		return 1;
	}
}

int parallel_to_secondary_diagonal(char **input_array, int x_axis, int y_axis, char* search_key, int rows, int columns)
{
	int iter_loop=x_axis,iter_loop2=y_axis,iter_loop3=0;
	while((iter_loop<rows && iter_loop2<columns) && search_key[iter_loop3]!='\0')
	{
		if(input_array[iter_loop][iter_loop2] == search_key[iter_loop3])
		{
			iter_loop2--;
			iter_loop3++;
			iter_loop++;
			continue;
		}
		else if(input_array[iter_loop][iter_loop2] != search_key[iter_loop3])
		{
			return 0;
		}
	}
	if(search_key[iter_loop3]=='\0')
	{
		return 1;
	}

}

int find_first_letter(char **input_array, int rows, int columns, char* search_key)
{
	int iter_loop, iter_loop2;
	for(iter_loop=0;iter_loop<rows;iter_loop++)
	{
		for(iter_loop2=0;iter_loop2<columns;iter_loop2++)
		{
			if(search_key[0] == input_array[iter_loop][iter_loop2])
			{
				if(1 == horizontal(input_array, iter_loop, iter_loop2, search_key, rows, columns))
				{
					return 1;
				}
				else if(1 == vertical(input_array, iter_loop, iter_loop2, search_key, rows, columns))
				{
					return 1;
				}
				else if(1 == parallel_to_primary_diagonal(input_array, iter_loop, iter_loop2, search_key, rows, columns))
				{
					return 1;
				}
				else if(1 == parallel_to_secondary_diagonal(input_array, iter_loop, iter_loop2, search_key, rows, columns))
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void test_check_string_in_matrix()
{
	char input_array[7][7] = {"MONISH", "APURVA", "VARSHA", "SIVANI", "VISHAL", "KISHAN"};
	int size_of_inputs[3] = {6,6};
	int iter_loop, iter_loop2,iter_loop3;
	int no_of_inputs = 6;
	char search_key[6][7]= {"KISHAN","MONISH","MAVSVK","HAAI","MPRAAN","SN"};
	char **input_matrix = (char**)calloc(size_of_inputs[0],sizeof(char*));
	for(iter_loop=0;iter_loop<size_of_inputs[1];iter_loop++)
	{
		input_matrix[iter_loop] = (char*)calloc(size_of_inputs[1]+1,sizeof(char));
	}

	for(iter_loop=0;iter_loop<size_of_inputs[0];iter_loop++)
	{
		for(iter_loop2=0;iter_loop2<size_of_inputs[1];iter_loop2++)
		{
			input_matrix[iter_loop][iter_loop2] = input_array[iter_loop][iter_loop2];
		}
	}
	for(iter_loop3=0;iter_loop3<no_of_inputs;iter_loop3++)
	{
		if(find_first_letter(input_matrix,size_of_inputs[0],size_of_inputs[1], search_key[iter_loop3]) == 1)
		{
			printf("FOUND\n");
		}
		else 
		{
			printf("NOT FOUND\n");
		}
	}
	for(iter_loop=0;iter_loop<size_of_inputs[1];iter_loop++)
	{
		free(input_matrix[iter_loop]);
	}
	free(input_matrix);
}

int _tmain(char argc, _TCHAR* argv[])
{
	test_check_string_in_matrix();
	getchar();
	return 0;
}