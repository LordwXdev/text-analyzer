#include"analyzer.h"
#include<stdio.h>


int analyze_file_stats(const char *path, Stats *out_stats)
{
    FILE *fp = fopen(path, "r");
    if(!fp) return 0;

    Stats s = {0,0,0};
    char line[4096];

    while (fgets(line, sizeof(line),fp))
    {
        s.lines++;
        s.chars += (long)strlen(line);

        int in_word = 0;
        for(size_t i = 0; line[i]; i++)
        {
            if(is_word_char((unsigned char)line[i]))
            {
                if(!in_word) 
                {
                    s.words++;
                    in_word = 1;
                }
                else 
                {
                    in_word = 0;
                }
            }
        }
    }
    fclose(fp);
    *out_stats = s;
    return 1;
}
int build_word_freq(const char *path)
{
    FILE *fp = fopen(path, "r");
    if(!fp) return 0;

    char word[256];
    int index = 0;
    int c;

    while ((c = fgetc(fp)) != EOF)
    {
        if (is_word_char((unsigned char)c))
        {
            if (index < 255)
                word[index++] = (char)c;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            add_word(word);  
            index = 0;
        }
    }

    if (index > 0)
    {
        word[index] = '\0';
        add_word(word);
    }

    fclose(fp);
    return 1;
}
void print_top_words(int top_n)
{
    for (int i = 0; i < top_n && i < word_count; i++)
    {
        printf("%s : %d\n", words[i].word, words[i].count);
    }
}
int count_word_in_file(const char *path, const char *query)
{
    FILE *fp = fopen(path, "r");
    if(!fp) return -1;

    char word[256];
    int index = 0;
    int c;
    int count = 0;

    while ((c = fgetc(fp)) != EOF)
    {
        if (is_word_char((unsigned char)c))
        {
            if (index < 255)
                word[index++] = (char)c;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            if (strcmp(word, query) == 0)
                count++;
            index = 0;
        }
    }

    fclose(fp);
    return count;
}

void free_word_freq()
{
    free(words);
    words = NULL;
    word_count = 0;
}