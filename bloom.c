#include<limits.h>

#include "bloom.h"
#include "hash.h"

#define SETBIT(a, n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

BF *bloom_create()
{
	return NULL;
}

int bloom_destroy()
{
	return 0;
}

int bloom_add()
{
	return 0;
}

int bloom_check()
{
	return 0;
}
