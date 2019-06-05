/*
** EPITECH PROJECT, 2019
** my_tab_contains
** File description:
** my_tab_contains
*/

#include "my.h"

int my_tab_contains_char(char **tab, char c)
{
    for (int i = 0; tab && tab[i]; ++i) {
        if (*tab[i] == c)
            return (1);
    }
    return (0);
}

int my_tab_contains_str(char **tab, char *str)
{
    for (int i = 0; tab && tab[i]; ++i) {
        if (!my_strcmp(tab[i], str))
            return (1);
    }
    return (0);
}