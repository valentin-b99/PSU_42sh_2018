/*
** EPITECH PROJECT, 2019
** my_tab_size
** File description:
** my_tab_size
*/

#include "./my.h"

int my_tab_size(char **tab)
{
    int res = 0;

    for (int i = 0; tab && tab[i]; ++i, ++res);
    return (res);
}