#include <stdio.h>
#include <string.h>
#include "analyzer.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <text_file>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];

    Stats stats;
    if (!analyze_file_stats(path, &stats)) {
        printf("Error: cannot open file.\n");
        return 1;
    }

    printf("\n--- File Statistics ---\n");
    printf("Lines : %ld\n", stats.lines);
    printf("Words : %ld\n", stats.words);
    printf("Chars : %ld\n", stats.chars);

    if (!build_word_freq(path)) {
        printf("Error building word frequency.\n");
        return 1;
    }

    printf("\n--- Top Words ---\n");
    print_top_words(10);

    free_word_freq();
    return 0;
}
