#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__

#include<stdlib.h>
#include<stdio.h>
#include"hash.h"
typedef struct {
	unsigned int size;
	unsigned char *a;

}BLOOM;

BLOOM *bloom_create(unsigned int size);
int bloom_add(BLOOM *bloom,char *s);
int bloom_check(BLOOM *bloom,char *s);
void bf_check(FILE *fp1,FILE *fp2,FILE *fp3);
#endif
