// S1Q10.cpp : Given an ascii string as input, write a function to convert that to integer format. example: input "1234" ouptut is 1234 (number)
//

#include "stdafx.h"

int string_length(char* input_array)
{
	int iter_loop=0;

	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

int exponent(int base, int power)
{
	int result=1, iter_loop;
	for(iter_loop=0;iter_loop<power;iter_loop++)
	{
		result *= base;
	}
	return result;
}

int string_rep_of_number_integer(char* input_array)
{
	int length = string_length(input_array)-1, result_integer=0, iter_loop = length,negative_input_flag=0;

	if(input_array[0] == '-')
	{
		negative_input_flag++;
	}

	while (iter_loop>=0)
	{
		if(negative_input_flag == 1 && iter_loop==0)
		{
			break;
		}
		if(input_array[iter_loop]<'0' && input_array[iter_loop]>'9')
		{
			printf("INVALID INPUT\n");
			return 0;
		}
		result_integer += (input_array[iter_loop] & ('p'-'a')) * exponent(10,length - iter_loop);
		iter_loop--;
	}

	if(negative_input_flag == 1)
	{
		return -result_integer;
	}
	else if(negative_input_flag == 0)
	{
		return result_integer;
	}
}

void test_string_rep_of_number_integer()
{
	char intput_array[6][10] = {
		{"1234"}, {"4321"},{"01233210"},{"12992831"},{"12344321"},{"-1234"}
							   };
	int output_array[6] = {1234, 4321, 1233210, 12992831, 12344321,-1234};

	int iter_loop;

	for(iter_loop=0;iter_loop<6;iter_loop++)
	{
		output_array[iter_loop] == string_rep_of_number_integer(intput_array[iter_loop]) ? printf("ACCEPTED\n") : printf("REJECTED\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_string_rep_of_number_integer();
	getchar();
	return 0;
}