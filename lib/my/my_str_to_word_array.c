/*
** EPITECH PROJECT, 2018
** my_str_to_wordtab
** File description:
** put each words of a string in an array
*/

#include "my.h"

int is_alphanum(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    if (c >= 'A' && c <= 'Z')
        return (1);
    if (c >= 'a' && c <= 'z')
        return (1);
    return (0);
}

char *epur_str(char *str)
{
    char *clean = malloc(my_strlen(str) + 1);
    int len = 0;

    if (clean == NULL)
        return (NULL);
    --str;
    while (*++str) {
        if (is_alphanum(*str)) {
            *clean++ = *str;
            ++len;
        }
        if (!is_alphanum(*str) && is_alphanum(*(str + 1))) {
            *clean++ = ' ';
            ++len;
        }
    }
    *clean = '\0';
    clean = (*(clean - len) == ' ') ? (clean - len + 1) : (clean - len);
    return (clean);
}

int count_words(char *str)
{
    int words = 0;
    int len = 0;

    --str;
    while (*++str) {
        if (!is_alphanum(*str))
            ++words;
        ++len;
    }
    ++words;
    str -= len;
    return (words);
}

void point_words(char **arr, char *str)
{
    int i = 0;
    int len = 0;

    arr[i++] = str;
    --str;
    while (*++str) {
        if (!is_alphanum(*str) && is_alphanum(*(str + 1)))
            arr[i++] = str + 1;
        ++len;
    }
    str -= len - 1;
    while (*++str) {
        if (!is_alphanum(*str))
            *str = '\0';
    }
    str -= len;
}

char **my_str_to_word_array(char *str)
{
    char *clean = epur_str(str);
    int words = count_words(clean);
    char **result = malloc(sizeof(char *) * (words + 1));

    point_words(result, clean);
    result[words] = NULL;
    return (result);
}
