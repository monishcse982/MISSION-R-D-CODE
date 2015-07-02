// S2Q8.cpp :  Given a string write a function (you will write test stubs and main too) to find the number of occurrences of each word in that string. "ram is playing. he is playing for last 2 hours. ram likes playing".
//

#include "stdafx.h"
#include "stdlib.h"

struct CHAIN_NODE
{
	char *data;
	int count;
	CHAIN_NODE *next;
};

struct TABLE_NODE
{
	char *data;
	int count;
	TABLE_NODE *next;
	CHAIN_NODE *chain_node;
};

TABLE_NODE** create_table(int n)
{
	int iter_loop=n;
	TABLE_NODE *head = (TABLE_NODE*)malloc(sizeof(TABLE_NODE));
	head->next = NULL;
	head->chain_node = NULL;
	head->data = NULL;
	head->count=0;
	TABLE_NODE *temp = head;
	iter_loop--;
	while(iter_loop>=1)
	{
		TABLE_NODE *new_node = (TABLE_NODE*)malloc(sizeof(TABLE_NODE));
		new_node->next = NULL;
		new_node->chain_node = NULL;
		new_node->data = NULL;
		new_node->count=0;
		temp->next  = new_node;
		temp = new_node;
		iter_loop--;
	}
	TABLE_NODE **table = (TABLE_NODE**)malloc((n+1)*sizeof(TABLE_NODE*));
	table[n] = '\0';
	temp = head;
	for(iter_loop=0;temp->next!=NULL;iter_loop++)
	{
		table[iter_loop] = temp;
		temp = temp->next;
	}
	table[iter_loop] = temp;
	return table;
}

int exponent(int base, int power)
{
	if(power == 0)
	{
		return 1;
	}

	while(power>0)
	{
		base = base * base;
		power--;
	}
	return base;
}

int hash (char *input, int table_size)
{
	int sum_of_ascii_values = 0, ascii_value, power = 0;
	unsigned long hash_key= *input;
	while(ascii_value = *input++)
	 {
		 sum_of_ascii_values+=(ascii_value*exponent(ascii_value,power));
		 hash_key+=((ascii_value*ascii_value)*exponent(ascii_value*ascii_value,power));
		 power++;
	 }
	return (sum_of_ascii_values * hash_key * (power+1))%table_size;
}

int string_compare(char *string1, char *string2)
{
	int iter_loop;
	for(iter_loop=0;string1[iter_loop]!='\0'||string2[iter_loop]!='\0';iter_loop++)
	{
		if(string1[iter_loop]!=string2[iter_loop])
		{
			return -1;
		}
	}
	if(string1[iter_loop]=='\0' && string2[iter_loop]=='\0')
	{
			return 1;
	}
}

void delete_hash_table(TABLE_NODE **table)
{
	int iter_loop=0,iter_loop2=0;
	while(table[iter_loop]!=NULL)
	{
		if(table[iter_loop]->data=='\0')
		{
			iter_loop++;
			continue;
		}
		if(table[iter_loop]->chain_node==NULL)
		{
			free(table[iter_loop]->data);
			iter_loop++;
			continue;
		}
		CHAIN_NODE *head = table[iter_loop]->chain_node;
		if(head->next==NULL)
		{
			free(head->data);
			free(table[iter_loop]->data);
			iter_loop++;
			continue;
		}
		CHAIN_NODE *temp, *next_node;
		next_node = head->next;
		while(next_node!=NULL)
		{
			temp = next_node->next;
			free(next_node->data);
			free(next_node);
			next_node = temp;
		}
	free(head->data);
	free(head);
	free(table[iter_loop]->data);
	iter_loop++;
	}
	free(table);
}

void insert_into_hash_table(TABLE_NODE **table, char *input_string, int hash_value)
{
	if(table[hash_value]->data==NULL)
	{
		table[hash_value]->data = input_string;
		table[hash_value]->count++;
		return;
	}
	
	else if((table[hash_value]->data!=NULL) && (string_compare(table[hash_value]->data,input_string)==1))
	{
		table[hash_value]->count++;
		return;
	}
	else if((table[hash_value]->data!=NULL) && (string_compare(table[hash_value]->data,input_string)==-1))
	{
		if(table[hash_value]->chain_node==NULL)
		{
			CHAIN_NODE *new_node = (CHAIN_NODE*)malloc(sizeof(CHAIN_NODE));
			new_node->data = input_string;
			new_node->next=NULL;
			new_node->count=1;
			table[hash_value]->chain_node = new_node;
			return;
		}
		else if(table[hash_value]->chain_node!=NULL)
		{
			CHAIN_NODE *head = table[hash_value]->chain_node;
			if(string_compare(head->data,input_string)==1)
			{
				head->count++;
				return;
			}
			else if(string_compare(head->data,input_string)==-1)
			{
				while(head->next!=NULL && string_compare(head->data,input_string)==-1)
				{
					head = head->next;
				}
				if(head->next==NULL && string_compare(head->data,input_string)==-1)
				{
					CHAIN_NODE *new_node = (CHAIN_NODE*)malloc(sizeof(CHAIN_NODE));
					new_node->data = input_string;
					new_node->next=NULL;
					new_node->count=1;
					head->next = new_node;
					return;
				}
				if(string_compare(head->data,input_string)==1)
				{
					head->count++;
				}
			}
		}
	}
}

TABLE_NODE** driver_for_word_frequency(char *input,int *table_size)
{
	int iter_loop=0;
	while(input[iter_loop]!='\0')
	{
		if(input[iter_loop]==' ')
		{
			*table_size = *table_size+1;
		}
		iter_loop++;
	}
	TABLE_NODE **table;
	table = create_table(*table_size);
	
	int iter_loop2=0,no_of_chars=0,iter_loop3=0,word_count=0;
	iter_loop=0;
	while(input[iter_loop]!='\0')
	{
		while((input[iter_loop2]>='a' && input[iter_loop2]<='z') || (input[iter_loop2]>='A' && input[iter_loop2]<='Z') || (input[iter_loop2]>='0' && input[iter_loop2]<='9'))
		{
			no_of_chars++;
			iter_loop2++;
		}

		char *word = (char*)calloc(no_of_chars+1,sizeof(char));
		no_of_chars=0;
		iter_loop3=0;
		while(iter_loop<iter_loop2)
		{
			word[iter_loop3] = input[iter_loop];
			iter_loop++;
			iter_loop3++;
		}
		insert_into_hash_table(table,word,hash(word,*table_size));
		while(!((input[iter_loop2]>='a' && input[iter_loop2]<='z') || (input[iter_loop2]>='A' && input[iter_loop2]<='Z') || (input[iter_loop2]>='0' && input[iter_loop2]<='9')))
		{
			if(input[iter_loop2] == '\0')
			{
				break;
			}
			iter_loop2++;
		}
		iter_loop = iter_loop2;
	}
	return table;
}

void test_word_frequency()
{
	char input[5][147] = {"ram is playing with ramlal. he is playing for last 2 hours. ram likes playing football with ramlal, they both belong to rameshwaram",
				"betty bought a bit of butter but the butter was a bit bitter so she added some better butter to the bitter butter to make the bitter butter better",
				"Larry Hurley, a burly squirrel hurler, hurled a furry squirrel through a curly grill",
				"I feel the feel you do Do you feel the feel I feel If you feel the feel I feel I too will feel the feel you feel",
				"which wristwatches are swiss wristwatches"
						 };
	char output[5][20][13] = {
{{"ram"},{"is"},{"playing"},{"with"},{"ramlal"},{"he"},{"for"},{"last"},{"2"},{"hours"},{"likes"},{"football"},{"they"},{"both"},{"belong"},{"to"},{"rameshwaram"}},

{{"betty"},{"bought"},{"a"},{"bit"},{"of"},{"butter"},{"but"},{"the"},{"was"},{"bitter"},{"so"},{"she"},{"added"},{"some"},{"better"},{"to"},{"make"}},

{{"Larry"},{"Hurley"},{"a"},{"burly"},{"squirrel"},{"hurler"},{"hurled"},{"furry"},{"through"},{"curly"},{"grill"}},

{{"I"},{"feel"},{"the"},{"you"},{"do"},{"Do"},{"If"},{"too"},{"will"}},

{{"which"},{"wristwatches"},{"are"},{"swiss"}}
							};

	int output_frequencies[5][20][2] = {
{{2},{2},{3},{2},{2},{1},{1},{1},{1},{1},{1},{1},{1},{1},{1},{1},{1}},

{{1},{1},{2},{2},{1},{5},{1},{3},{1},{3},{1},{1},{1},{1},{2},{2},{1}},

{{1},{1},{3},{1},{2},{1},{1},{1},{1},{1},{1}},

{{4},{11},{3},{4},{1},{1},{1},{1},{1}},

{{1},{2},{1},{1}}
							};


	int iter_loop,iter_loop2,iter_loop3;
	for(iter_loop=0;iter_loop<5;iter_loop++)
	{
		int table_size = 0;
		TABLE_NODE **table = driver_for_word_frequency(input[iter_loop],&table_size);
		int accepted_flag=0;
		for(iter_loop2=0;((output[iter_loop][iter_loop2][0]>='a'&&output[iter_loop][iter_loop2][0]<='z')||(output[iter_loop][iter_loop2][0]>='A'&&output[iter_loop][iter_loop2][0]<='Z')||(output[iter_loop][iter_loop2][0]>='0'&&output[iter_loop][iter_loop2][0]<='9'));iter_loop2++)
		{
			int hash_value  = hash(output[iter_loop][iter_loop2],table_size);
			if((string_compare(table[hash_value]->data,output[iter_loop][iter_loop2])==1) && table[hash_value]->count==output_frequencies[iter_loop][iter_loop2][0])
			{
				accepted_flag=1;
				continue;
			}
			CHAIN_NODE *head = table[hash_value]->chain_node;
			while(head!=NULL)
				{
					if((string_compare(head->data,output[iter_loop][iter_loop2])==1) && head->count==output_frequencies[iter_loop][iter_loop2][0])
					{
						accepted_flag=1;
						break;
					}
					head = head->next;
				}
		}
		if(accepted_flag==0)
			{
				printf("REJECTED\n");
			}
			else if(accepted_flag==1)
			{
				printf("ACCEPTED\n");
			}
		delete_hash_table(table);
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	test_word_frequency();
	getchar();
	return 0;
}