// S2Q5.cpp : Given a string as input, see whether the words of the string are palindrome or not. example: "god is god" returns true. "god is great" is not a palindrome of words
//

#include "stdafx.h"

int string_length(char* input_array)
{
	int iter_loop=0;
	while(input_array[iter_loop+1]!='\0')
	{iter_loop++;}
	return iter_loop;
}

int word_to_word_palindrome(char* input_array)
{
	int start_of_word = 0, end_of_word = string_length(input_array),current_position;
	while(start_of_word<=end_of_word)
	{
		while(input_array[end_of_word-1]!=' ')
		{
			end_of_word--;
		}

		current_position = end_of_word-2;

		while(input_array[end_of_word+1]!=' ' && input_array[end_of_word+1]!='\0')
		{
		if(input_array[start_of_word] != input_array[end_of_word])
		{
			return 0;
		}
		start_of_word++;
		end_of_word++;
		}
		end_of_word = current_position;
		start_of_word+=2;
	}
	return 1;
}

void test_word_to_word_palindrome()
{
	char input_array[6][21] = {"god is god", "ABC DEF ABC", "ABC", "ABC DEF GHI DEF ABC","ABC DEF","god is great"};
	int iter_loop;
	for(iter_loop=0;iter_loop<6;iter_loop++)
	{
		int result = word_to_word_palindrome(input_array[iter_loop]);
		if(result == 1)
		{
			printf("PALINDROME\n");
		}
		else if(result == 0)
		{
			printf("NOT A PALINNDROME\n");
		}

	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_word_to_word_palindrome();
	getchar();
	return 0;
}

