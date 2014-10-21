all: strfind

strfind: bloom.o main.o hash.o trie.o
	cc -o strfind -Wall -pedantic bloom.o main.o hash.o trie.o

bloom.o: bloom.c bloom.h hash.h
	cc -o bloom.o -Wall -pedantic -ansi -c bloom.c

main.o: main.c trie.h
	cc -o main.o -Wall -pedantic -ansi -c main.c

hash.o: hash.c hash.h
	cc -o hash.o -Wall -pedantic -ansi -c hash.c

trie.o: trie.c trie.h
	cc -o trie.o -Wall -pedantic -ansi -c trie.c
