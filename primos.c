#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DEFAULT_FIRST ULLONG_MAX
//#define DEFAULT_FIRST 100


unsigned long long int find_divisor(unsigned long long int n)
	{
	register unsigned long long int i, last_divisor;
	if (n <= 3)
		return 1;
	if (n%2 == 0)
		return 2;
	last_divisor = n/2;
	for (i = 3; i <= last_divisor; i += 2)
		if (n%i == 0)
			return i;
		else
			last_divisor = n/i;
	return 1;
	}


int main(int argc, char *argv[])
	{
	register unsigned long long int first, i, divisor;
	setbuf(stdout, NULL);
	if (argc == 1)
		first = DEFAULT_FIRST;
	else if (argc == 2)
		first = strtoull(argv[1], NULL, 0);
	else
		{
		printf("Usage: %s <first_number>\n", argv[0]);
		return 1;
		}
	if (first%2 == 0)
		first--;
	for (i = first; i>=2; i-=2)
		{
		divisor = find_divisor(i);
		if (divisor == 1)
			{			
			printf("%llu IS PRIME\n", i);
			return 0;
			}
		else
			printf("%llu is divisible by %llu\n", i, divisor);
		}
	return 0;
	
	//printf("%llu\n", ULLONG_MAX);
	//printf("%llu\n", first);
	}
	
	
	
	
	
	
