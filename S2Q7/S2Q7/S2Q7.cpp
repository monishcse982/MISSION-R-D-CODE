// S2Q7.cpp : Given a string which has an expression like "a = 1234 + bcd + 23 * p - 234" find the maximum number in the string and the token (or variable) with maximum characters. for the given example 1234 is the maximum number and bcd is the maximum char variable
//

#include "stdafx.h"
void maximum_number(char* input_array)
{
	int iter_loop = 0,start_index_of_result,length_of_result = 0,temp_index,temp_length=0;
	while(input_array[iter_loop]!='\0')
	{
		if((input_array[iter_loop]>='0' && input_array[iter_loop]<='9'))
		{
			if((iter_loop>0) && ((input_array[iter_loop-1]>='0' && input_array[iter_loop-1]<='9') || ((input_array[iter_loop-1]>='a'&&input_array[iter_loop-1]<='z')||(input_array[iter_loop-1]>='A'&&input_array[iter_loop-1]<='Z'))))
			{
				iter_loop++;
				continue;
			}

			temp_index = iter_loop;
			iter_loop++;
		
			while((input_array[iter_loop]!='\0') && (input_array[iter_loop]>='0' && input_array[iter_loop]<='9'))
			{
				temp_length++;
				iter_loop++;
			}

			if(length_of_result<temp_length)
			{
				length_of_result = temp_length;
				start_index_of_result = temp_index;
			}
			else if(length_of_result==temp_length && input_array[start_index_of_result]<input_array[temp_index])
			{
				length_of_result = temp_length;
				start_index_of_result = temp_index;
			}

		}
		temp_length = 0;
		iter_loop++;
	}
	for(iter_loop=start_index_of_result;length_of_result>=0;iter_loop++,length_of_result--)
	{
		printf("%c",input_array[iter_loop]);
	}
} 

void longest_string(char* input_array)
{
	int iter_loop = 0,start_index_of_result,length_of_result = 0,temp_index,temp_length=0;
	while(input_array[iter_loop]!='\0')
	{
		if((input_array[iter_loop]>='a' && input_array[iter_loop]<='z') || (input_array[iter_loop]>='A' && input_array[iter_loop]<='Z'))
		{
			temp_index = iter_loop;
			iter_loop++;
		
			while((input_array[iter_loop]>='a'&&input_array[iter_loop]<='z') || (input_array[iter_loop]>='a'&&input_array[iter_loop]<='z') || (input_array[iter_loop]>='0'&&input_array[iter_loop]<='9'))
			{
				temp_length++;
				iter_loop++;
			}
			if(length_of_result<temp_length)
			{
			start_index_of_result = temp_index;
			length_of_result = temp_length;
			}
		}
		temp_length = 0;
		iter_loop++;
	}
	for(iter_loop=start_index_of_result;length_of_result>=0;iter_loop++,length_of_result--)
	{
		printf("%c",input_array[iter_loop]);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	char input_array[2][56] = {"ab = 1234 + bcd + 234 * p - 234 / dedhs6eh * y234553645","a = 1234 + bcd + 23 * p - 234"};
	int iter_loop;
	for(iter_loop=0;iter_loop<2;iter_loop++)
	{
		longest_string(input_array[iter_loop]);
		printf("\t");
		maximum_number(input_array[iter_loop]);
		
	printf("\n");
	}
	getchar();
	return 0;
}