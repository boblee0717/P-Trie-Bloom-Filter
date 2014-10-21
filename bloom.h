#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__

#include<stdlib.h>

typedef struct {
unsigned int size;
/*other fields*/
}BF;

BF *bloom_create();
int bloom_destroy();
int bloom_add();
int bloom_check();

#endif
