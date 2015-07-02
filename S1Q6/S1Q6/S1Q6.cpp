// S1Q6.cpp : Given a string (without length) as input, write a function to remove all non alphabets and digits from the same string (string should be passed as call by reference). example: input: "ab$23#44" output "ab2344"

//

#include "stdafx.h"
#include "string.h"

char* only_alphanumeric(char* input_array)
{
	int loop1=0,loop2;
	char temp_char;
	while(input_array[loop1]!='\0')
	{
		if(!((input_array[loop1]>='a' && input_array[loop1]<='z') || (input_array[loop1]>='A' && input_array[loop1]<='Z') || (input_array[loop1]>='0' && input_array[loop1]<='9')))
		{
			loop2 = loop1;
			while(input_array[loop2+1]!='\0')
			{
				temp_char = input_array[loop2];
				input_array[loop2] = input_array[loop2+1];
				input_array[loop2+1] = temp_char;
				loop2++;
			}
			input_array[loop2] = '\0';
		}
		if(((input_array[loop1]>='a' && input_array[loop1]<='z') || (input_array[loop1]>='A' && input_array[loop1]<='Z') || (input_array[loop1]>='0' && input_array[loop1]<='9')))
		{loop1++;}
	}
	return (input_array);
}

void test_only_aphanumeric()
{
	char input_array[2][12] = {
								{"ab$23#44"},
								{"v1ar@@5u1*7"}
							  };

	char output_array[2][12] = {
								{"ab2344"},
								{"v1ar5u17"}
							   };
	char *return_ptr;
	int loop1,loop2,result=0;
	for(loop1=0;loop1<2;loop1++)
	{
		return_ptr = only_alphanumeric(input_array[loop1]);
		loop2 = 0;
		while(return_ptr[loop2]!='\0')
		{
			if(return_ptr[loop2] == output_array[loop1][loop2])
			{
				loop2++;
				continue;
			}
			else
			{
				result++;
				break;

			}

		}
		if(result == 0)
		{
			printf("ACCEPTED\n");
		}
		else
		{
			result--;
			printf("REJECTED\n");
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	test_only_aphanumeric();
	getchar();
	return 0;
}

