#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

typedef struct StrInfo
{
    uint64_t lines, characters, words;
} StrInfo;

StrInfo count_str(const char* str)
{
    if (strcmp(str, "") == 0)
    {
        return (StrInfo) { .lines = 0, .characters = 0, .words = 0 };
    }

    StrInfo info =
    {
        .lines = 1, //If the string is not empty, it must have at least one line
        .characters = 0,
        .words = 0
    };

    int index = 0;
    bool in_word = false;
    while (str[index] != '\0')
    {
        bool got_into_word = isalpha(str[index]) && str[index] != ' ';
        if (in_word)
        {
            if (!got_into_word) //If the word is over
            {
                in_word = false;
                info.words++;
            }
        }
        else
        {
            if (got_into_word)
            {
                in_word = true;
            }
        }

        if (str[index] == '\n')
        {
            info.lines++;
        }
        if (isprint(str[index]))
        {
            info.characters++;
        }

        index++;
    }

    return info;
}

StrInfo count_file(FILE* file)
{
    uint64_t max_char_count = 256;
    char* str = (char*)calloc(max_char_count, sizeof(char));
    if (str == NULL)
    {
        printf("Memory error, terminating.\n");
        exit(1);
    }

    uint64_t char_count = 0;
    while (!feof(file))
    {
        char c = '\0';
        if ((c = fgetc(file)) != EOF)
        {
            if (char_count >= max_char_count)
            {
                max_char_count *= 2;
                str = realloc(str, max_char_count);
                if (str == NULL)
                {
                    printf("Memory error, terminating.\n");
                    exit(1);
                }
            }
            str[char_count] = c;
            char_count++;
        }
    }

    StrInfo info = count_str(str);
    free(str);
    return info;
}

void printstrinfo(StrInfo info)
{
    printf("%zu word(s), %zu character(s), %zu line(s)\n", info.words, info.characters, info.lines);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage Schemes:\n");
        printf("wlc -s <string> => Prints the characters, words and lines in the given string.\n");
        printf("wlc <file1> <file2> ... => Prints the characters, words and lines in the given files.\n");
        return 1;
    }

    //Handle -s flag
    if (strcmp(argv[1], "-s") == 0)
    {
        if (argc < 3)
        {
            printf("String not provided.\n");
            return 1;
        }
        StrInfo info = count_str(argv[2]);
        printstrinfo(info);
        return 0;
    }

    //Handle default behaviour (files word counting)
    for (int i = 1; i < argc; i++)
    {
        FILE* file = fopen(argv[i], "rt");
        printf("%s: ", argv[i]);
        if (file != NULL)
        {
            StrInfo info = count_file(file);
            printstrinfo(info);
            fclose(file);
        }
        else
        {
            printf("%s\n", strerror(errno));
        }
    }

    return 0;
}
