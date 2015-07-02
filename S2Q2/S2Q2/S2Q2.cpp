// S2Q2.cpp : Given a string include space between all characters. only space should be there between every character. before first character and after last character of the string there shoudlnt be any spaces. "abcd efgh" should be converted as "a b c d e f g h". space given in input should be removed.
//

#include "stdafx.h"
#include "stdlib.h"
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

int length_of_array(char *input_array)
{
	int iter_loop = 0;
	while(input_array[iter_loop]!='\0')
	{
		iter_loop++;
	}
	return iter_loop;
}

void include_space_between_letters(char* input_array)
{
	strip_spaces(input_array);
	int iter_loop=1,iter_loop2, length = length_of_array(input_array);
	while(input_array[iter_loop]!='\0')
	{
		iter_loop2 = length_of_array(input_array);
		while(iter_loop2 >=iter_loop)
		{
			input_array[iter_loop2+1] = input_array[iter_loop2];
			iter_loop2-=1;
		}
		input_array[iter_loop] = ' ';
		iter_loop+=2;
	}
}

void test_include_space_between_letters()
{
	char input_array[2][10] = {"abcd efgh", "a     d"};
	char output_array[2][16] = {"a b c d e f g h", "a d"};
	int iter_loop,iter_loop2,no_of_letters=0;
	
	for(iter_loop=0;iter_loop<2;iter_loop++)
	{
		for(iter_loop2=0;input_array[iter_loop][iter_loop2]!='\0';iter_loop2++)
		{
			no_of_letters++;
		}

		char *input_string = (char*)calloc((2*no_of_letters)-1,sizeof(char));
		no_of_letters = 0;
		for(iter_loop2=0;input_array[iter_loop][iter_loop2]!='\0';iter_loop2++)
		{
			input_string[iter_loop2] = input_array[iter_loop][iter_loop2];
		}
		include_space_between_letters(input_string);
		if(strcmp(input_string,output_array[iter_loop])==0)
		{
			printf("ACCEPTED\n");
		}
		else if(strcmp(input_string,output_array[iter_loop])!=0)
		{
			printf("REJECTED\n");
		}
		free(input_string);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_include_space_between_letters();
	getchar();
	return 0;
}