#ifndef __TRIE_H__
#define __TRIE_H__

struct node {
    char *s;
    struct node *left;
    struct node *right;
};

struct huffman_node {
    int c;
    int left;
    int right;
    int priority;
    int used;
};

#define node struct node
#define huffman_node struct huffman_node
int huff_c[70];
huffman_node huffman[2000];
char lib[70][100];

char * change(char *s) ;
node *createNode();
void add(char *s,node *root,int l_or_r,node *parent);
int lookup(char *s2,node *root);
void trie_check(FILE* fp1,FILE *fp2,FILE *fp3);
void init_huffman(FILE* fp);
void dfs(int now,char *s);
int getInt(char c);
#endif
