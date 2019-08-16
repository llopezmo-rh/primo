#include <gmp.h>
#include <stdio.h>

#define MAX_LENGTH 100
#define DEFAULT_FIRST "1000000000000000000000000"

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

// find_divisor returns 0 (false) if no divisor different to 1 has been found
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

int main()
	{
	mpz_t i;
	mpz_init_set_str(i, DEFAULT_FIRST, 10);
	
	if (mpz_even_p(i))
		mpz_add_ui(i, i, 1);
	
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
