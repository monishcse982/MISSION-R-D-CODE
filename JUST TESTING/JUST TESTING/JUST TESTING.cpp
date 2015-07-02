// JUST TESTING.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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
	int sum_of_ascii_values = 0, ascii_value, multipicant = 11, power = 0;
	unsigned long hash_key=0;
	while(ascii_value = *input++)
	 {
		 sum_of_ascii_values+=ascii_value;
		 hash_key+=(ascii_value*exponent(multipicant,power));
		 power++;
	 }
	return (sum_of_ascii_values + hash_key)%table_size;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char input[7] = "MONISH";
	printf("\nFINAL HASH KEY: %d",hash(input,14));
	getchar();
	return 0;
}

