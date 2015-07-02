// S2Q1.cpp : Given a string as input,remove all spaces that are in the given string. example "abcd efgh p q r " shoudl be converted as "abcdefghpqr". dont allocate new string. same string should be converted to the above form.
//

#include "stdafx.h"
#include "string.h"

void strip_spaces(char* input_array)
{
	int iter_loop=0;
	while(input_array[iter_loop]!='\0')
	{
		if(input_array[iter_loop] == ' ')
		{
			int iter_loop2 = iter_loop;
			char temp;
			while(input_array[iter_loop2+1] != '\0')
			{
				temp = input_array[iter_loop2];
				input_array[iter_loop2] = input_array[iter_loop2+1];
				input_array[iter_loop2+1] = temp;
				iter_loop2++;
			}
			input_array[iter_loop2] = '\0';
		}
		if(input_array[iter_loop]!=' ')
		{
		iter_loop++;
		}
	}
}

void test_strip_spaces()
{
	char input_array[6][20] = {
									"abcd   efgh p q r  ",
									" ",
									"   abc   ",
									"          ",
									" abcd   efgh p q r",
									"abc"
							  };

	char output_array[6][14] = {
									"abcdefghpqr",
									"",
									"abc",
									"",
									"abcdefghpqr",
									"abc"
							   };
	int iter_loop;
	for(iter_loop=0;iter_loop<6;iter_loop++)
	{
		strip_spaces(input_array[iter_loop]);
		if(strcmp(input_array[iter_loop],output_array[iter_loop])==0)
		{
			printf("ACCEPTED\n");
		}
		else if(strcmp(input_array[iter_loop],output_array[iter_loop])!=0)
		{
			printf("REJECTED\n");
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_strip_spaces();
	getchar();
	return 0;
}