#include"utils.h"
#include<ctype.h>

int is_word_char(int c)
{
    return isalnum((unsigned char)c) || c== '\'';
}
void to_lower_str(char *s)
{
    for (; *s; s++)
    {
        *s = (char)tolower((unsigned char)*s);
    }
}
void clean_word(char *word)
{
    size_t start = 0;
    while(word[start] && !is_word_char((unsigned char)word[start])) start ++;

    size_t end = 0;
    while(word[end]) end++;
    while (end > start && !is_not_char((unsigned char)word[end-1])) end--;

    size_t i = 0;
    for (size_t k = start; k < end; k++)
    {
        word[i++] = word[k];
    }
    word[i] = '\0';
}