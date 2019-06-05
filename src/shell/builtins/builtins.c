/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int my_env(shell_t *ft, __attribute__ ((unused)) char **tab)
{
    ll_t *tmp = ft->env;

    while (tmp) {
        my_printf("%s\n", tmp->data);
        tmp = tmp->next;
    }
    return (0);
}

int my_unsetenv(shell_t *ft, char **tab)
{
    ll_t *tmp = ft->env;
    int i = 1;
    int len = 0;

    if (!tab[1]) {
        write(2, tab[0], my_strlen(tab[0]));
        write(2, ": Too few arguments.\n", 21);
        ft->rc = 1;
        return (0);
    }
    len = my_strlen(tab[i]);
    while (tmp && (my_strncmp(tmp->data, tab[i], len) != 0
    || tmp->data[len] != '=')) {
        tmp = tmp->next;
        len = my_strlen(tab[i]);
    }
    if (!tmp)
        return (0);
    ll_remove_node(&ft->env, tmp);
    return (ft->rc);
}

int my_setenv(shell_t *ft, char **tab)
{
    if (!tab[1])
        my_env(ft, tab);
    else if (tab[2] && tab[3]) {
        write(2, tab[0], my_strlen(tab[0]));
        write(2, ": Too many arguments.\n", 22);
        ft->rc = 1;
        return (ft->rc);
    } else {
        my_setenv_two(ft, tab);
    }
    return (ft->rc);
}

int my_setenv_two(shell_t *ft, char **tab)
{
    if ((tab[1][0] < 'A' || tab[1][0] > 'Z') &&
        (tab[1][0] < 'a' || tab[1][0] > 'z')) {
        write(2, tab[0], my_strlen(tab[0]));
        write(2, ": Variable name must begin with a letter.\n", 42);
        ft->rc = 1;
    } else if (my_str_is_alphanum(tab[1]))
        ll_update_node(ft, &ft->env, tab[1], tab[2]);
    else {
        write(2, tab[0], my_strlen(tab[0]));
        write(2, ": Variable name must contain alphanumeric characters.\n", 54);
        ft->rc = 1;
    }
    return (0);
}

int my_exit(shell_t *ft, char **tab)
{
    ft = ft;
    tab = tab;
    exit(0);
    return (0);
}
