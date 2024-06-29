all: trie

trie: trie.cpp Makefile
	g++ trie.cpp -o trie -std=c++23 -g -O3 -Wall -Wextra -pedantic -Wno-unused-parameter -fmax-errors=5 -DNDEBUG

clean:
	rm -rf trie


