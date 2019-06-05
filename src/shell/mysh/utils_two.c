/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int my_strlen_tab(char **tab)
{
    int i = 0;

    while (tab[i])
        i++;
    return (i);
}
