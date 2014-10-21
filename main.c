#include<stdio.h>
#include<string.h>
#include "trie.h"
#include "bloom.h"
void init(char *argv[]) {
	FILE *fp_strpool;
	FILE *fp_inited_strpool;
	char line[1024];
	int len,i,flag,cnt=0;
	fp_strpool = fopen(argv[1],"r");
	fp_inited_strpool = fopen("strpooled.dat","w");
	while(fgets(line,1024,fp_strpool)) {
		len = strlen(line);
		flag = 1;
		for(i=0;i<len;i++) {
			if(line[i]=='\n' || line[i]=='\r')
				continue;
			if(!((line[i]>='a'&&line[i]<='z')||(line[i]>='A'&&line[i]<='Z')
					||(line[i]>='0'&&line[i]<='9')
					||(line[i]=='.'||line[i]=='-'||line[i]=='_'||line[i]=='@'))) {
				flag = 0;
				break;
			}
		}
		if(flag==0) {
			cnt++;
		}
		else {
			fprintf(fp_inited_strpool,"%s",line);
		}
	}
	printf("The num of not allowed is %d\n",cnt);
	fclose(fp_strpool);
	fclose(fp_inited_strpool);
}

int main(int argc, char *argv[])
{
	FILE *fp_strpool;
	FILE *fp_checkedmail;
	FILE *fp_result;
	FILE *fp_strpooled;

	if(argc<2) {
		fprintf(stderr, "ERROR: No word file specified\n");
		return -1;
	}
	fp_strpool = fopen(argv[1],"r");
	fp_checkedmail = fopen(argv[2],"r");
	fp_result = fopen(argv[3],"w");
	printf("Now we will init the strpool.dat........\n");
	init(argv);
	printf("The init done........\n");
	fp_strpooled = fopen("strpooled.dat","r");
	printf("We will build the trie and match the strings\n");
	trie_check(fp_strpooled,fp_checkedmail,fp_result);
	printf("The trie match done!\n");
	printf("Next is Bloom Filter Match.......\n");
	fseek(fp_strpooled, 0, SEEK_SET);
	fseek(fp_checkedmail, 0, SEEK_SET);
	bf_check(fp_strpooled,fp_checkedmail,fp_result);
	return 0;
}
