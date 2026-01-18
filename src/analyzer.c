#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "analyzer.h"
#include"utils.h"

//this for practice

/* ===============================
   Helper: check if char is part of a word
   =============================== */
int is_word_char(unsigned char c)
{
    return isalnum(c);
}

/* ===============================
   File statistics (lines, words, chars)
   =============================== */
int analyze_file_stats(const char *path, Stats *out_stats)
{
    FILE *fp = fopen(path, "r");
    if (!fp) return 0;

    Stats s = {0, 0, 0};
    char line[4096];

    while (fgets(line, sizeof(line), fp)) {
        s.lines++;
        s.chars += (long)strlen(line);

        int in_word = 0;
        for (size_t i = 0; line[i] != '\0'; i++) {
            if (is_word_char((unsigned char)line[i])) {
                if (!in_word) {
                    s.words++;
                    in_word = 1;
                }
            } else {
                in_word = 0;
            }
        }
    }

    fclose(fp);
    *out_stats = s;
    return 1;
}

/* ===============================
   Word frequency storage
   =============================== */
typedef struct {
    char word[64];
    int count;
} WordEntry;

static WordEntry *entries = NULL;
static int entry_count = 0;
static int entry_capacity = 0;

/* ===============================
   Add or update a word
   =============================== */
static void add_word(const char *w)
{
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(entries[i].word, w) == 0) {
            entries[i].count++;
            return;
        }
    }

    if (entry_count == entry_capacity) {
        entry_capacity = (entry_capacity == 0) ? 16 : entry_capacity * 2;
        entries = realloc(entries, entry_capacity * sizeof(WordEntry));
    }

    strcpy(entries[entry_count].word, w);
    entries[entry_count].count = 1;
    entry_count++;
}

/* ===============================
   Build word frequency from file
   =============================== */
int build_word_freq(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) return 0;

    char word[64];
    int idx = 0;
    int c;

    while ((c = fgetc(fp)) != EOF) {
        if (is_word_char((unsigned char)c)) {
            if (idx < 63)
                word[idx++] = tolower(c);
        } else if (idx > 0) {
            word[idx] = '\0';
            add_word(word);
            idx = 0;
        }
    }

    if (idx > 0) {
        word[idx] = '\0';
        add_word(word);
    }

    fclose(fp);
    return 1;
}

/* ===============================
   Print top N words
   =============================== */
void print_top_words(int top_n)
{
    for (int i = 0; i < entry_count && i < top_n; i++) {
        printf("%s : %d\n", entries[i].word, entries[i].count);
    }
}

/* ===============================
   Count a specific word in file
   =============================== */
int count_word_in_file(const char *path, const char *query)
{
    FILE *fp = fopen(path, "r");
    if (!fp) return -1;

    char word[64];
    int idx = 0;
    int c;
    int count = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (is_word_char((unsigned char)c)) {
            if (idx < 63)
                word[idx++] = tolower(c);
        } else if (idx > 0) {
            word[idx] = '\0';
            if (strcmp(word, query) == 0)
                count++;
            idx = 0;
        }
    }

    if (idx > 0) {
        word[idx] = '\0';
        if (strcmp(word, query) == 0)
            count++;
    }

    fclose(fp);
    return count;
}

/* ===============================
   Free allocated memory
   =============================== */
void free_word_freq(void)
{
    free(entries);
    entries = NULL;
    entry_count = 0;
    entry_capacity = 0;
}
