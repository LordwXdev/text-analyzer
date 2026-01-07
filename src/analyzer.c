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
    
}
void print_top_words(int top_n)
{

}
int count_word_in_file(const char *path, const char *query)
{

}

void free_word_freq(void);