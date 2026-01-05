#ifndef ANALYZER_H
#define ANALYZER_H

typedef struct 
{
    long lines;
    long words;
    long chars;
}Stats;

int analyze_file_stats(const char *path, Stats *out_stats);
int build_word_freq(const char *path);
void print_top_words(int top_n);
int count_word_in_file(const char *path, const char *query);

void free_word_freq(void);


#endif