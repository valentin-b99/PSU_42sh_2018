/*
** EPITECH PROJECT, 2019
** prompt
** File description:
** prompt
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int my_put_rc(int nb)
{
    int mod;
    char tmp = 0;

    if (nb >= 10){
        mod = nb % 10;
        nb = (nb - mod) / 10;
        my_put_rc(nb);
        tmp = (mod % 10) + 48;
        write(0, &tmp, 1);
    } else {
        tmp = nb + 48;
        write(0, &tmp, 1);
    }
    return (0);
}

int display_prompt(shell_t *ft)
{
    char *dir = ll_find(ft->env, "PWD");

    write(0, !ft->rc ? "\033[1;32m" : "\033[1;31m", 7);
    if (dir) {
        if (my_strcmp(dir, "/")) {
            my_revstr(dir);
            *my_strstr(dir, "/") = 0;
            my_revstr(dir);
        }
        write(0, dir, my_strlen(dir));
        write(0, " ", 1);
        free(dir);
    }
    write(0, "[", 1);
    my_put_rc(ft->rc);
    write(0, "] ", 2);
    write(0, "$> ", 3);
    write(0, "\033[0m", 4);
    return (0);
}