#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <gmp.h>

// If the loop reaches a number with more ciphers than MAX_LENGTH, it will stop
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
	// Removing buffer to send output to stdout immediately
	setbuf(stdout, NULL);
	
	// Getting options
	int opt;
	int prime_break = 0;
	unsigned long int n_output = 0;
	while ((opt = getopt (argc, argv, "bn:")) != -1)
		switch (opt)
			{
			case 'b':
				prime_break = 1;
				break;
			case 'n':
				n_output = strtoul(optarg, NULL, 10);
				break;
			case '?':
				// First option does not seem to be necessary
				if (optopt == 'n')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				fprintf(stderr, "Usage: %s [-b] [-n <n_output>] [starting_value]\n", argv[0]);
				return 1;
			default:
				fprintf(stderr, "Usage: %s [-b] [-n <n_output>] [starting_value]\n", argv[0]);
				return 1;
			}	
	
	// Setting first value of "i", which will be the loop index
	mpz_t i;
	if (optind<argc)
		mpz_init_set_str(i, argv[optind], 10);
	else
		mpz_init_set_str(i, DEFAULT_FIRST, 10);		
		
	// Validating first value of "i"
	if (mpz_cmp_ui(i, 2) < 0)
		{
		fprintf(stderr, "Fatal error: starting number must be an integer greater than or equal to 2\n");
		return 2;
		}		
	if (mpz_sizeinbase(i, 10)>MAX_LENGTH)
		{
		fprintf(stderr, "Fatal error: number cannot have more than "STRINGIFY(MAX_LENGTH)" ciphers\n");
		return 3;
		}
	
	// Making sure that first value of "i" is odd
	if (mpz_even_p(i))
		mpz_add_ui(i, i, 1);
	
	// Starting the loop. "i" will be increased 2 units per interaction in
	// order to skip even numbers
	char i_str[MAX_LENGTH];
	char divisor_str[MAX_LENGTH];
	mpz_t divisor;
	int count = 1;
	do
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
			if (prime_break)
				break;
			}
		mpz_clear(divisor);
		mpz_add_ui(i, i, 2);
		if (n_output>0 && ++count>n_output)
			break;
		} while (mpz_sizeinbase(i, 10)<=MAX_LENGTH);
		
	//mpz_clear(i);
	//mpz_clear(divisor);
	return 0;	
	}
