/*
** EPITECH PROJECT, 2018
** task05
** File description:
** return < 0 if str1 < str2, = 0 if str1 = str2
** > 0 if str1 > str2
*/

#include "my.h"

char *stricmp_tolower(char const *str)
{
    int j = -1;
    char *res = NULL;

    while (str[++j]);
    if (!(res = malloc(sizeof(char) * (j + 1))))
        return (NULL);
    for (int i = 0; str[i]; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            res[i] = str[i] + 32;
        else
            res[i] = str[i];
    }
    return (res);
}

int my_stricmp(char const *s1, char const *s2)
{
    char *l1 = stricmp_tolower(s1);
    char *l2 = stricmp_tolower(s2);
    int ret = 0;
    int i = 0;

    for (; *l1 == *l2; ++l1, ++l2, ++i) {
        if (*l1 == '\0') {
            free(l1 - i);
            free(l2 - i);
            return (0);
        }
    }
    ret = (*(unsigned char *)l1 < *(unsigned char *)l2) ? -1 : 1;
    free(l1 - i);
    free(l2 - i);
    return (ret);
}