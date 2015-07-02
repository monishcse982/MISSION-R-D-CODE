// S3Q3.cpp : Given a string with many words, count the frequncy of the given word using recursion. string length is given to you already
//

#include "stdafx.h"

int word_frequency_count(char* input_string, char* input_word, int start_index)
{
	static int count = 0;
	if(input_string==NULL)
	{
		printf("INVALID STRING\n");
		return 0;
	}
	if(input_word==NULL)
	{
		printf("INVALID SEARCH WORD\n");
		return 0;
	}
	if(input_string[start_index]=='\0')
	{
		return 0;
	}
	int iter_loop = 0, word_not_found_flag=0;
	while((input_string[start_index]<'A' || input_string[start_index]>'Z') && (input_string[start_index]<'a' || input_string[start_index]>'z'))
	{
		start_index++;
	}
	while(input_string[start_index]!='\0' && input_string[start_index]!=' ' && input_word[iter_loop]!='\0' && ((input_string[start_index]>='A' || input_string[start_index]<='Z') && (input_string[start_index]>='a' || input_string[start_index]<='z')))
	{
		if(input_string[start_index]==input_word[iter_loop])
		{
			start_index++;
			iter_loop++;
			continue;
		}
		if(input_string[start_index]!=input_word[iter_loop])
		{
			start_index++;
			word_not_found_flag++;
			break;
		}
	}
	if(((input_string[start_index]>='A' && input_string[start_index]<='Z') || (input_string[start_index]>='a' && input_string[start_index]<='z'))
		||
		((input_string[start_index]==' ' || input_string[start_index]=='\0') && (input_word[iter_loop]!='\0')))
	{
		word_not_found_flag++;
	}
	if(word_not_found_flag>0)
	{
		while(input_string[start_index]!='\0' && input_string[start_index]!=' ')
		{
			start_index++;
		}
		return word_frequency_count(input_string,input_word,start_index);
	}
	else if(word_not_found_flag==0)
	{
		count++;
		return 1+word_frequency_count(input_string,input_word,start_index+1);
	}
}

void test_word_frequency_count()
{
	char input_string[3][149] = {
	"betty bought a bit of butter, but the bit of butter was bitter so betty added better butter into the bitter butter to make the bitter butter better.",
	"ram likes playing. ram is playing with ramlal in rameshwaram. ram is playing tennis.",
	"she sells sea shells by the sea shore. But if she sells sea shells by the sea shore then where are the sea shells she sells"
								};

	char input_words[3][5][12] = {
									{"butter","bitter","betty","bit"},
									{"ram","ramlal","playing","rameshwaram"},
									{"sea","shells","sells"}
							    };

	int expected_frequency[3][4] = {{5,3,2,2},{3,1,3,1},{5,3,3}};
	int iter_loop,iter_loop2,iter_loop3;
	for(iter_loop=0;iter_loop<3;iter_loop++)
	{
		for(iter_loop2=0;iter_loop2<4;iter_loop2++)
		{
			int result = word_frequency_count(input_string[iter_loop],input_words[iter_loop][iter_loop2],0);
			(result == expected_frequency[iter_loop][iter_loop2])?printf("ACCEPTED\n"):printf("REJECTED\n");
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_word_frequency_count();
	getchar();
	return 0;
}