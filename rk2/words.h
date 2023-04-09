#ifndef WORDS_H
#define WORDS_H

#define MATMAX 5
#define WORDMAX 10

#define RET_SUCCESS 0
#define INPUT_ERR 1

typedef char word_t[WORDMAX + 1];

void init(word_t **mat, word_t *buf, int n, int m);
int inputwords(word_t **words, int n, int m);
// int getword(word_t w);
void printwords(word_t **words, int n, int m);

void sortwords(word_t **words, int n, int m);
int get_sum_length(word_t *words, int n);
void swapwords(word_t **a, word_t **b);

#endif // !WORDS_H
