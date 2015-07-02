// S2Q4.cpp : Given a string reverse the words of the string. example: input "matt is a teacher" should be converted as "teacher a is matt". remember same string shoudl be changed. no extra array should be allocated
//

#include "stdafx.h"
#include "string.h"

int string_length(char* input_array)
{
	int iter_loop=0;
	while(input_array[iter_loop+1]!='\0')
	{iter_loop++;}
	return iter_loop;
}

void reverse_string(char* input_array)
{
	int start_of_string = 0, end_of_string = string_length(input_array);
	char temp;
	while(start_of_string <= end_of_string)
	{
		temp = input_array[start_of_string];
		input_array[start_of_string] = input_array[end_of_string];
		input_array[end_of_string] = temp;
		start_of_string++;
		end_of_string--;
	}
}

void reverse_word(char* input_array, int start_of_word, int end_of_word)
{
	char temp;
	while(start_of_word < end_of_word)
	{
		temp = input_array[start_of_word];
		input_array[start_of_word] = input_array[end_of_word];
		input_array[end_of_word] = temp;
		start_of_word++;
		end_of_word--;
	}
}

void word_to_word_reverse(char* input_array)
{
	int start_of_word = 0, end_of_word;
	while(input_array[start_of_word]!='\0')
	{
		end_of_word = start_of_word;
		while((input_array[end_of_word+1]!=' ') && (input_array[end_of_word+1]!='\0'))
		{end_of_word+=1;}
		reverse_word(input_array,start_of_word,end_of_word);
		start_of_word = end_of_word+2;
	}
	reverse_string(input_array);
}

void test_word_to_word_reverse()
{
	char input_array[5][46] = {"GOOGLE IS THE BEST SEARCH ENGINE IN THE WORLD", " ", "GOOGLE", "matt is a teacher", "THIS IS"};
	char output_array[5][46] = {"WORLD THE IN ENGINE SEARCH BEST THE IS GOOGLE", " ", "GOOGLE", "teacher a is matt", "IS THIS"};

	for(int iter_loop=0;iter_loop<5;iter_loop++)
	{
		word_to_word_reverse(input_array[iter_loop]);
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
	test_word_to_word_reverse();
	getchar();
	return 0;
}