/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int check_signals(shell_t *ft, int return_valu)
{
    if (return_valu == 512)
        return (((ft->rc = 2) >> 2) | 1);
    if (WTERMSIG(return_valu) == 11) {
        ft->rc = 139;
        write(1, "Segmentation fault", 18);
        if (WCOREDUMP(return_valu))
            write(1, " (core dumped)", 14);
        my_printf("\n");
        return (1);
    }
    if (WTERMSIG(return_valu) == 8) {
        ft->rc = 136;
        write(1, "Floating exception", 18);
        if (WCOREDUMP(return_valu))
            write(1, " (core dumped)", 14);
        my_printf("\n");
        return (1);
    }
    return (0);
}

void check_return_value(char **execve_tab, shell_t *ft)
{
    if (errno == EACCES) {
        write(1, execve_tab[0], my_strlen(execve_tab[0]));
        write(1, ": Permission denied.\n", 21);
        ft->rc = 1;
        exit(1);
    }
    if (errno == ENOEXEC) {
        write(1, execve_tab[0], my_strlen(execve_tab[0]));
        write(1, ": Exec format error. Wrong Architecture.\n", 41);
        ft->rc = 1;
        exit(1);
    }
}
