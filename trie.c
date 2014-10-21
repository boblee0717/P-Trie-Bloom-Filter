#include<limits.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "trie.h"

int getInt(char c) {

    if(c>='a'&&c<='z')
        return c-'a';
    if(c>='A'&&c<='Z')
        return c-'A'+26;
    if(c>='0'&&c<='9')
        return c-'0'+52;
    if(c=='.')
        return 62;
    if(c=='@')
        return 63;
    if(c=='_')
        return 64;
    if(c=='-')
        return 65;
    return -1;
}


void dfs(int now,char *s) {
    int i;
    char *s2;
    int len = strlen(s);
    if(huffman[now].left == -1 && huffman[now].right == -1) {
        for(i=0;i<len;i++) {
            lib[huffman[now].c][i] = s[i];
        }
        lib[huffman[now].c][i] = '\0';
        return;
    }
    s2 = (char *)malloc(sizeof(char)*(len+2));
    for(i=0;i<len;i++) {
        s2[i] = s[i];
    }
    s2[i+1] = '\0';
    if(huffman[now].left != -1) {
        s2[i] = '0';
        dfs(huffman[now].left,s2);
    }
    if(huffman[now].right != -1) {
        s2[i] = '1';
        dfs(huffman[now].right,s2);
    }
    free(s2);
}

void init_huffman(FILE* fp) {
    char line[1024];
    int i,len,tmp,size;
    int tmp1,tmp2;
    int max1,max2;
    int root = -1;
    char *s = "";
    memset(huff_c,0,sizeof(huff_c));

    while(fgets(line,1024,fp)) {
        len = strlen(line);
        for(i=0;i<len;i++) {
            tmp = getInt(line[i]);
            if(tmp!=-1)
                huff_c[tmp]++;
        }
    }

    for(i=0;i<66;i++) {
        huffman[i].c = i;
        huffman[i].priority = huff_c[i];
        huffman[i].left = -1;
        huffman[i].right = -1;
        huffman[i].used = 0;
    }
    len = 66;
    size = 66;
    while(1) {
        if(len == 1) {
            for(i=0;i<size;i++) {
                if(huffman[i].used == 0) {
                    root = i;
                    break;
                }
            }
            break;
        }
        else {
            tmp1 = -1;
            tmp2 = -1;
            max1 = 0x3f3f3f3f;
            max2 = 0x3f3f3f3f;
            for(i=0;i<size;i++) {
                if(huffman[i].used)
                    continue;
                if(huffman[i].priority < max1) {
                    tmp2 = tmp1;
                    max2 = max1;
                    tmp1 = i;
                    max1 = huffman[i].priority;
                    continue;
                }
                if(huffman[i].priority < max2) {
                    tmp2 = i;
                    max2 = huffman[i].priority;
                    continue;
                }
            }

            huffman[tmp1].used = 1;
            huffman[tmp2].used = 1;
            huffman[size].used = 0;
            huffman[size].left = tmp1;
            huffman[size].right = tmp2;
            huffman[size].priority = max1+max2;
            size++;
            len--;
        }
    }

    dfs(root,s);

}


char *change(char *s) {
    int i,j,k,len,len2,tmp;
    char *ret;
    len = strlen(s);
    len2 = 0;
    for(i=0;i<len;i++) {
        if(s[i]=='\n' || s[i]=='\r')
            break;
        len2 += strlen(lib[getInt(s[i])]);
    }
    ret = (char *)malloc(sizeof(char)*len2+1);
    for(i=0,j=0;i<len;i++) {
        if(s[i]=='\n' || s[i]=='\r')
            break;
        tmp = getInt(s[i]);
        len2 = strlen(lib[tmp]);

        for(k=0;k<len2;k++) {
            ret[j++] = lib[tmp][k];
        }
    }
    ret[j] = '\0';
    return ret;
}

node *createNode() {
    node * ret = (node *)malloc(sizeof(node));
    ret->s = NULL;
    ret->left = NULL;
    ret->right = NULL;
    return ret;
}

void add(char *s,node *root,int l_or_r,node *parent) {
    node *now = root;
    int i,j,k,lens,lenroot;
    node *tmp;
    node *tmp2;
    node *tmp3;

    if(now == NULL) {
        now = (node*) malloc(sizeof(node));
        now->s = (char*)malloc(sizeof(char)*strlen(s));
        strcpy(now->s,s);
        if(l_or_r == -1) parent->left = now;
        else parent->right = now;
        return;
    }

    lens = strlen(s);
    lenroot = strlen(now->s);

    for(i=0;i<lens && i<lenroot;i++)
        if(s[i] != now->s[i])
            break;

    if(i==lens) {
        if(i==lenroot)
            return;
        else {
            tmp = createNode();
            tmp->s = (char *)malloc(sizeof(char)*(lens+2));
            strcpy(tmp->s,s);
            tmp2 = createNode();
            tmp2->s = (char *)malloc(sizeof(char)*(lenroot-i+2));
            for(j=0,k=i+1;k<lenroot;k++,k++)
                tmp2->s[j] = now->s[k];
            tmp2->s[j] = '\0';
            tmp2->left = now->left;
            tmp2->right = now->right;
            if(now->s[lens] == '0')
                tmp->left = tmp2;
            else
                tmp->right = tmp2;

            if(l_or_r == -1)
                parent->left = tmp;
            else
                parent->right = tmp;
            if(now != NULL)
                free(now);
            return;
        }
    }
    else if(i == lenroot) {
        if(s[i]=='0')
            add(s+i+1,now->left,-1,now);
        else
            add(s+i+1,now->right,1,now);
    }
    else {
        tmp = createNode();
        tmp->s = (char *)malloc(sizeof(char)*(i+1));
        for(j=0;j<i;j++)
            tmp->s[j] = s[j];
        tmp->s[j] = '\0';

        tmp2 = createNode();
        tmp2->s = (char *)malloc(sizeof(char)*(lenroot-i+2));
        for(j=0,k=i+1;k<lenroot;k++,j++)
            tmp2->s[j] = now->s[k];
        tmp2->s[j] = '\0';
        tmp2->left = now->left;
        tmp2->right = now->right;

        tmp3 = createNode();
        tmp3->s = (char *)malloc(sizeof(char)*(lens-i+2));
        for(j=0,k=i+1;k<lens;k++,j++)
            tmp3->s[j] = s[k];
        tmp3->s[j] = '\0';

        if(s[i] == '0') {
            tmp->left = tmp3;
            tmp->right = tmp2;
        }
        else {
            tmp->right = tmp3;
            tmp->left = tmp2;
        }

        if(l_or_r == -1)
            parent->left = tmp;
        else
            parent->right = tmp;
        if(now != NULL)
            free(now);
        return;
    }



}

int lookup(char *s2,node *root) {
    int len,lennow;
    int i,j;
    node *p = root;
    len = strlen(s2);
    lennow = strlen(p->s);
    i=0;
    j=0;
    while(i<len) {
        for(;i<len && j<lennow;i++,j++)
            if(s2[i] != p->s[j])
                break;
        if(j<lennow) return 0;
        else {
            if(i==len) return 1;
            if(s2[i] == '0') {
                if(p->left != NULL) {
                    p = p->left;
                    lennow = strlen(p->s);
                    i++;
                    j=0;
                }
                else
                    return 0;
            }
            else {
                if(p->right != NULL) {
                    p = p->right;
                    lennow = strlen(p->s);
                    i++;
                    j=0;
                }
                else {
                    return 0;
                }
            }
        }
    }
    if(p->s == NULL) return 1;
    else return 0;
}


void trie_check(FILE* fp1,FILE *fp2,FILE *fp3) {
    node* Trie = (node*)malloc(sizeof(node));
    char line[1024];
    char *s;
    int cnt = 0;
    int cnt2 = 1;
    FILE* fpt = fp1;
    printf("Now we will init the huffman code........\n");
    init_huffman(fpt);
    printf("Now init the huffman code done........\n");
    printf("Now we will add the data from input file to build a trie .......\n");
    fseek(fp1, 0, SEEK_SET);
    while(fgets(line,1024,fp1)) {
        s = change(line);
        add(s,Trie->left,-1,Trie);
        if(cnt2%1000000==0) {
            printf("has add %d\n",cnt2);
        }
        cnt2++;
    }
    printf("Now the building has done and we will match strings........\n");
	fprintf(fp3,"-------------------------------------Trie Match-------------------------------------------\n");
    while(fgets(line,1024,fp2)) {
        s = change(line);
        if(!lookup(s,Trie->left)) {
            fprintf(fp3,"%d no\n",cnt);
        }
        free(s);
        cnt++;
    }

}
