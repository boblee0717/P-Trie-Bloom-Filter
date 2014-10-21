#include<limits.h>
#include<stdio.h>
#include<string.h>
#include "bloom.h"
#define SETBIT(a, n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

BLOOM *bloom_create(unsigned int size)
{
	BLOOM *bloom;
	if(!(bloom=malloc(sizeof(BLOOM)))) return NULL;
	if(!(bloom->a = calloc((size+CHAR_BIT-1)/CHAR_BIT,sizeof(char)))){
		free(bloom);
		return NULL;
	}
	bloom->size = size;
	return bloom;
}


int bloom_add(BLOOM *bloom,char *s)
{
	unsigned int k = 0;
	unsigned int b = 0;
	unsigned int len = strlen(s);
	for(k=0;k<11;k++) {
		switch(k) {
			case 0: b=RSHash(s,len);
			 		break;
			case 1: b=JSHash(s,len);
					break;
			case 2: b=PJWHash(s,len);
					break;
			case 3: b=ELFHash(s,len);
					break;
			case 4: b=BKDRHash(s,len);
					break;
			case 5: b=SDBMHash(s,len);
					break;
			case 6: b=DJBHash(s,len);
					break;
			case 7: b=DEKHash(s,len);
					break;
			case 8: b=BPHash(s,len);
					break;
			case 9: b=FNVHash(s,len);
					break;
			case 10: b=APHash(s,len);
					break;
		}
		SETBIT(bloom->a,b%bloom->size);
	}
	return 0;
}

int bloom_check(BLOOM *bloom,char *s){

	unsigned int k = 0;
	unsigned int b = 0;
	unsigned int len = strlen(s);
	for(k=0;k<11;k++) {
		switch(k) {
			case 0: b=RSHash(s,len);
			 		break;
			case 1: b=JSHash(s,len);
					break;
			case 2: b=PJWHash(s,len);
					break;
			case 3: b=ELFHash(s,len);
					break;
			case 4: b=BKDRHash(s,len);
					break;
			case 5: b=SDBMHash(s,len);
					break;
			case 6: b=DJBHash(s,len);
					break;
			case 7: b=DEKHash(s,len);
					break;
			case 8: b=BPHash(s,len);
					break;
			case 9: b=FNVHash(s,len);
					break;
			case 10: b=APHash(s,len);
					break;
		}
		if(!GETBIT(bloom->a,b%bloom->size))
			return 0;
	}
	return 1;
}

void bf_check(FILE* fp1,FILE* fp2,FILE *fp3) {
	BLOOM *bloom ;
	char line[1024];
	int pos = -1;
	bloom = bloom_create(239620000);
	printf("Create done\n");
	while(fgets(line,1024,fp1))
		bloom_add(bloom,line);
	printf("add done\n");
	fprintf(fp3,"-------------------------------------Bloom Filter Match-------------------------------------------\n");
	while(fgets(line,1024,fp2)) {
		pos++;
		if(!bloom_check(bloom,line))
			fprintf(fp3,"%d no\n",pos);
	}
}
