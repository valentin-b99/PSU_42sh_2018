/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int find_unset_var(shell_t *ft, char *dif)
{
    var_t *tmp = ft->var;

    while (tmp) {
        if (my_strncmp(tmp->name, dif, my_strlen(dif)) == 0) {
            ll_delete_variables(&ft->var, tmp);
            return (1);
        }
    }
    return (0);
}

int my_unset_var(shell_t *ft, char **tab)
{
    for (int i = 1; tab[i] != NULL; i += 1)
        find_unset_var(ft, tab[i]);
    return (strtwt_free_tab(tab) | 0);
}

int find_same_variables(shell_t *ft, char *var)
{
    var_t *tmp = ft->var;

    while (tmp) {
        if (my_strcmp(tmp->name, var) == 0) {
            ll_delete_variables(&ft->var, tmp);
            break;
        }
        tmp = tmp->next;
    }
    return (0);
}