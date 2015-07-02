// l_adder.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<stdlib.h>
#include<string.h>
struct node{
	int num;
	node* next;
};
void my_strcat(char* str1, char* str2)
{
	int farrar_par1 = 0, farray_par2 = 0;
	while (str1[farrar_par1] != '\0'){ farrar_par1++; }
	while (str2[farray_par2] != '\0'){
		str1[farrar_par1] = str2[farray_par2];
		farrar_par1++;
		farray_par2++;
	}
	str1[farrar_par1] = '\0';
}
int my_strcmp(char* str1, char* str2)
{
	int str_size1 = 0, str_size2 = 0, flag = 0;
	while (str1[str_size1++] != '\0'){}
	while (str2[str_size2++] != '\0'){}
	if (str_size1 != str_size2) return 1;
	int array_par = 0;
	while (str1[array_par] != '\0')
	{
		if (str1[array_par] != str2[array_par]) flag = 1;
		array_par++;
	}
	return flag;
}
struct test
{
	char inp1[30];
	char inp2[30];
	char out[30];
}testcase[10] = { 
{ "1123456", "24","1,1,2,3,4,8,0" },
{ "123456", "7589","131045" },
{ "5555", "44445", "" },
{ "4567", "6789", "" },
{ "1235", "56", "" },
{"56","1235"},


};
node* insert(node* head, int i)
{
	node* temp = (node*)malloc(sizeof(node));
	node* temp1;
	temp1 = head;
	if (head == NULL)
	{
		temp->num = i;
		temp->next = NULL;
		head = temp;
	}
	else{
		while (temp1->next != NULL)
			temp1 = temp1->next;
		temp->num = i;
		temp->next = NULL;
		temp1->next = temp;
	}
	return head;
}


int my_atoi(char *arr)
{
	int farray_par = 0, num = 0, flag = 1;
	while (arr[farray_par] == ' '){ farray_par++; }                //traverse until non space character is encountered
	while (arr[farray_par] != '\0')
	{
		if (arr[farray_par] == '-' && (farray_par == 0 || arr[farray_par - 1] == ' '))
		{
			flag = -1;                                              //if there is '-' character set flag to -1,so that we can return negative number
		}
		else if (arr[farray_par] == '+'){}                          //neglect the character if it is '+'
		else if (!(arr[farray_par] >= 48 && arr[farray_par] <= 57))
		{
			return 0;                                               //if it is non digit return 0
		}
		else
		{
			num = num * 10 + arr[farray_par] - 48;                  //convert digits into num

		}
		farray_par++;
	}
	return flag*num;
}
node* reverse(node* head, node* pre, node* temp)
{
	if (head == NULL)
		return NULL;
	else if (head->next == NULL)
	{
		head->next = pre;
		return head;
	}
	else
	{
		temp = (head->next)->next;
		(head->next)->next = head;
		head = head->next;
		(head->next)->next = pre;
		pre = head;
		if (temp != NULL)head = reverse(temp, pre, NULL);
		return head;
	}
}
node* create_list(char *arr)
{
	int arr_par = 0;
	node* head = NULL;
	char* word = (char*)malloc(2*sizeof(char));
	while (arr[arr_par] != '\0')
	{
		word[0] = arr[arr_par]; word[1] = '\0';
		head = insert(head, my_atoi(word));
		arr_par++;
	}
	return head;
}
int add(node* head1, node* head2,int carry)
{
	int a;
	if (head1 == NULL&&head2 == NULL&&carry==1)
	{
		return 2;
	}
	else if (head1 == NULL){
		head2->num += carry; return 1;
	}
	else if (head2 == NULL){
		head1->num += carry;
		return 0;
	}
	a = (head1->num + head2->num)+carry;
	head1->num =a%10;
	head2->num = a%10;
	if (a/10 ==1) return add(head1->next, head2->next, 1);
	else
	return add(head1->next, head2->next, 0);
}
node* l_adder(node* head1, node* head2)
{
	int n = 0, carry = 0;
	node* pre = NULL;
	node* temp = NULL;
	head1 = reverse(head1, pre, temp);
	head2 = reverse(head2, pre, temp);
	n = add(head1, head2, carry);
	if (n == 1)
	{
		return reverse(head2, NULL, NULL);
	}
	else if (n == 0)
		return reverse(head1, NULL, NULL);
	else
	{
		head1 = reverse(head1, NULL, NULL);
		node* f_node = (node*)malloc(sizeof(node));
		f_node->num = 1;
		f_node->next = head1;
		head1 = f_node;
		return head1;
	}
}
node* l_adder2(node* head1, node* head2)
{
	node* head11 = head1;
	node* head22 = head2;
	int length1 = 0, length2 = 0;
	while (head11 != NULL)
	{
		length1++;
		head11 = head11->next;
	}
	while (head22 != NULL)
	{
		length2++;
		head22 = head22->next;
	}
	head11 = (length1 > length2) ? head1 : head2;
	head22 = (head11 == head2) ? head1 : head2;
	node* n_node = (node*)malloc(sizeof(node));
	n_node->num = 0;
	n_node->next = head11;
	int dif = 0, sum = 0;
	node* ct1 = n_node;
	for (dif = 0; dif<((length1>length2) ? (length1 - length2) : (length2 - length1)); dif++)
	{
		if (head11->num == 9){}
		else
		{
			ct1 = head11;
		}
		head11 = head11->next;
	}
	while (head11 != NULL)
	{
		sum = head11->num + head22->num;
		head11->num = sum % 10;
		if (sum < 9)
		{
			ct1 = head11;
		}
		else
		{
			while (ct1 != head11)
			{
				ct1->num = (ct1->num + 1) % 10;
				ct1 = ct1->next;
			}
        }
		head11 = head11->next;
		head22 = head22->next;
    }
	head11 = (length1 > length2) ? head1 : head2;
	if (n_node->num == 1)
	{
		head11 = n_node;
	}
	return head11;
}
void testcases()
{
	int tno;
	for (tno = 0; tno < 6; tno++)
	{

		int array_par, str_size = 0, flag = 0;
		node* head1 = NULL;
		node* head2 = NULL;
		while (testcase[tno].inp1[str_size++] != '\0'){}
		char *array1 = (char*)malloc(str_size*sizeof(char));
		for (array_par = 0; array_par < str_size; array_par++)
		{
			array1[array_par] = testcase[tno].inp1[array_par];
		}
		head1 = create_list(array1);
		str_size = 0;
		while (testcase[tno].inp2[str_size++] != '\0'){}
		char *array2 = (char*)malloc(str_size*sizeof(char));
		for (array_par = 0; array_par < str_size; array_par++)
		{
			array2[array_par] = testcase[tno].inp2[array_par];
		}
		head2 = create_list(array2);
		head1 = l_adder2(head1, head2);
		while (head1 != NULL)
		{
			printf_s("%d", head1->num);
			head1 = head1->next;
		}
		printf("\n");
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	testcases();
	getchar();
	return 0;
}