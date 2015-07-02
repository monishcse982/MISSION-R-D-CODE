// S1Q9.cpp : Given an integer as input, write a function to convert that to ascii format. example: 1234 number, output : "1234" ascii string
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"

int length_of_integer(int* integer)
{
	int length=0, input = *integer;
	if(input == 0)
	{
		return 1;
	}
	while(input>0)
	{
		input/=10;
		length++;
	}
	return length;
}

char* integer_to_string_rep_of_num(int* input)
{
	if(*input == 0)
	{
		return "0";
	}

	int length = length_of_integer(input);                             //length_of_integer() is  user defined function for finding the number of bits in an integer.
	char *result = (char*) calloc ((length+1) , (sizeof(char)));     //length+1 to avoid memory leaks.                                         
	length--;
	while(*input>0)
	{
		result[length] = (*input)%10 | ('q' - 'A');              //Masking of bits to 1 in the 8-bit binary representation of the number to get the ASCII value of the integer.
		*input /= 10;
		length--;
	}
	
	return result;
}

void test_integer_to_string_rep_of_num()
{
	int input_array[10] = {1234,1,0,120};
	char output_array[5][5] = {
								{"1234"},
								{"1"},
								{"0"},
								{"120"}
							  };

	for(int iter_loop=0;iter_loop<4;iter_loop++)
	{
		if(strcmp(output_array[iter_loop], integer_to_string_rep_of_num(&input_array[iter_loop])) == 0)
		{

			printf("ACCEPTED\n");

		}
		else if(!(strcmp(output_array[iter_loop], integer_to_string_rep_of_num(&input_array[iter_loop])) == 0))
		{
			printf("REJECTED\n");
		}

	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_integer_to_string_rep_of_num();
	getchar();
	return 0;
}