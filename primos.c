#include <gmp.h>
#include <stdio.h>

//#define MAX_LENGTH 100
#define DEFAULT_FIRST "100000"

int main()
	{
	mpz_t nFirst;
	char nStr[] = DEFAULT_FIRST;
	
	mpz_init(nFirst);
	mpz_set_ui(nFirst,0);
	
	mpz_t dummy;
	mpz_init(dummy);
	mpz_set_ui(dummy,0);
	if (mpz_mod_ui (dummy, nFirst, 2)%2 == 0)
		mpz_sub_ui (nFirst, nFirst, 1);
		
	
	
	
	}
