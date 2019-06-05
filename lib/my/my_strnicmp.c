/*
** EPITECH PROJECT, 2018
** task06
** File description:
** same as my_strcmp but it stops at n or
** at end of line if n is greater
*/

#include "my.h"

int my_strnicmp(char const *s1, char const *s2, int n)
{
    char *l1 = stricmp_tolower(s1);
    char *l2 = stricmp_tolower(s2);
    int ret = 0;
    int i = 0;

    for (; n > 0; ++l1, ++l2, --n, ++i) {
        if (*l1 != *l2) {
            ret = (*(unsigned char *)l1 < *(unsigned char *)l2) ? -1 : 1;
            free(l1 - i);
            free(l2 - i);
            return (ret);
        } else if (*l1 == '\0') {
            free(l1 - i);
            free(l2 - i);
            return (0);
        }
    }
    return (0);
}