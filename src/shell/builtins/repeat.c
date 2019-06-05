/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int repeat_errors(shell_t *ft, char **tab)
{
    if (!tab[1] || !tab[2]) {
        write(2, "repeat: Too few arguments.\n", 27);
        ft->rc = 1;
        return (84);
    }
    if (my_str_isnum(tab[1]) == 0) {
        write(2, "repeat: Badly formed number.\n", 29);
        ft->rc = 1;
        return (84);
    }
    return (0);
}

int my_repeat(shell_t *ft, char **tab)
{
    int turn = 0;
    int rc = 0;

    if (repeat_errors(ft, tab) == 84)
        return (84);
    turn = my_getnbr(tab[1]);
    for (int i = 0; i < turn; ++i) {
        if (!my_strcmp(tab[2], "repeat"))
            rc = my_repeat(ft, &tab[2]);
        else if (is_builtin(&tab[2], ft) != -1);
        else
            get_access_and_fork(ft, &tab[2]);
        if (rc == 84)
            return (84);
    }
    ft->rc = 0;
    return (0);
}
