#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

#include <stdio.h>

/* ===============================
   Statistics structure
   =============================== */
typedef struct {
    long lines;
    long words;
    long chars;
} Stats;

/* ===============================
   File analysis functions
   =============================== */
int analyze_file_stats(const char *path, Stats *out_stats);

/* ===============================
   Word frequency functions
   =============================== */
int build_word_freq(const char *path);
void print_top_words(int top_n);
int count_word_in_file(const char *path, const char *query);
void free_word_freq(void);

/* ===============================
   Helper functions
   =============================== */
int is_word_char(unsigned char c);

#endif
