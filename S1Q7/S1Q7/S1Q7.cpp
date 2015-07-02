// S1Q7.cpp : Given a string (without length) as input, write a function to convert all upper case characters to lower case and lower case characters to upper case. example: GooD as input and output is "gOOd".

//

#include "stdafx.h"
#include "string.h"

void change_case(char* input_array)
{
	int iter_loop = 0;
	while(input_array[iter_loop]!='\0')
	{
		if(input_array[iter_loop] >= 'a' && input_array[iter_loop]<='z')
		{
			input_array[iter_loop] &= (~('a'-'A'));
		}
		else if(input_array[iter_loop] >= 'A' && input_array[iter_loop]<='Z')
		{
			input_array[iter_loop] |=('a'-'A');
		}
		iter_loop++;
	}
}

void test_case_change()
{
	char input_array[10][10] = {
								"MoNiSh", "aPuRvA", "BRADY", "tata", "a","A","Aa","zZ", "ANghe8as", "Mo1994nI"
							  };
	char output_array[10][10] = {
								"mOnIsH", "ApUrVa", "brady", "TATA", "A", "a", "aA", "Zz", "anGH8AS", "mO1994Ni"
							   };
	int  iter_loop;

	for(iter_loop=0;iter_loop<8;iter_loop++)
	{
		change_case(input_array[iter_loop]);
		(strcmp(output_array[iter_loop],input_array[iter_loop]) == 0) ? printf("ACCEPTED\n") : printf("REJECTED\n"); 

	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_case_change();
	getchar();
    return 0;
}