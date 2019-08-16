#include <stdio.h>
#include <gmp.h>

// Maximum ciphers. If the loop reaches a longer number, it will stop
#define MAX_LENGTH 100

// In case no argument is introduced, this will be the first number to be calculated
#define DEFAULT_FIRST "1000000000000000000000000"

// This allows to use constants on input/output instructions
#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)


// find_divisor stores on "divisor" the first divisor of "n" found different to 1.
// If none is found, it will set "divisor" to 1.
// It returns 0 (false) if no divisor different to 1 has been found. Otherwise 1
int find_divisor(mpz_t divisor, const mpz_t n)
	{
	mpz_init_set_ui(divisor, 1);
	if (mpz_even_p(n))
		{
		mpz_set_ui(divisor, 2);
		return 1;
		}	
	mpz_t i;
	mpz_init_set_ui(i, 3);
	mpz_t last_divisor;
	mpz_init (last_divisor);
	mpz_cdiv_q_ui(last_divisor, n, 2);
	while (mpz_cmp(i, last_divisor) <= 0)
		{
		if (mpz_divisible_p(n, i))
			{
			mpz_set(divisor, i);
			break;
			}
		else
			{
			mpz_cdiv_q(last_divisor, n, i);
			mpz_add_ui(i, i, 2);
			}
		}
	mpz_clear(i);
	mpz_clear(last_divisor);
	if (mpz_cmp_ui(divisor, 1) == 0)
		return 0;
	else
		return 1;	
	}

int main(int argc, char *argv[])
	{
	// Removing buffer to receive output on stdout immediately
	setbuf(stdout, NULL);
	
	// Setting "i", which will be the loop index
	mpz_t i;
	if (argc == 1)
		mpz_init_set_str(i, DEFAULT_FIRST, 10);
	else
		mpz_init_set_str(i, argv[1], 10);
	
	// Making sure that first value of "i" is odd
	if (mpz_even_p(i))
		mpz_add_ui(i, i, 1);
	
	// Starting the loop. "i" will be increased 2 units per interaction
	char i_str[MAX_LENGTH];
	char divisor_str[MAX_LENGTH];
	mpz_t divisor;
	for(;;)
		{
		if (find_divisor(divisor, i))
			{
			mpz_get_str(divisor_str, 10, divisor);
			mpz_get_str(i_str, 10, i);			
			printf("%s is divisible by %s\n", i_str, divisor_str);
			}
		else
			{
			mpz_get_str(i_str, 10, i);
			printf("%s IS PRIME\n", i_str);
			//break;
			}
		mpz_clear(divisor);
		mpz_add_ui(i, i, 2);
		if (mpz_sizeinbase(i, 10)>MAX_LENGTH)
			{
			fprintf(stderr, "Maximum number length reached: "STRINGIFY(MAX_LENGTH)" ciphers\n");
			break;
			}
		}
		
	mpz_clear(i);
	mpz_clear(divisor);
	return 0;	
	}
