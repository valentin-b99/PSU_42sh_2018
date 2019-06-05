/*
** EPITECH PROJECT, 2019
** errors.c
** File description:
** errors
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int set_err_return(shell_t *ft)
{
    ft->rc = 1;
    return (84);
}

int parenthesis_error(char **tab)
{
    int par = 0;
    char *first = my_strdup(tab[0]);

    for (int i = 0; tab[i]; i++)
        for (int j = 0; tab[i][j]; j++)
            (tab[i][j] == '(' || tab[i][j] == ')') ? (par++) : (0);
    if (!par)
        return (write(2, "foreach: Too few arguments.\n", 28));
    if (tab[0][0] != '(')
        return (write(2, "foreach: Words not parenthesized.\n", 34));
    if (tab[my_tab_size(tab) - 1][my_strlen(tab[my_tab_size(tab) - 1]) - 1]
    != ')')
        return (write(2, "foreach: Words not parenthesized.\n", 34));
    tab[0] = malloc(sizeof(char) * my_strlen(first));
    if (!tab)
        return (84);
    tab[0] = my_strcpy(tab[0], first + 1);
    tab[my_tab_size(tab) - 1][my_strlen(tab[my_tab_size(tab) - 1]) - 1] = 0;
    return (0);
}