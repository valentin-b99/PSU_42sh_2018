/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int get_idx_from_addr(char *str, char *addr)
{
    int idx = 0;
    char *tmp = str;

    while (tmp != addr) {
        tmp += 1;
        idx += 1;
    }
    return (idx);
}

int remove_cote(char *str)
{
    char *addr = NULL;

    while ((addr = my_strstr(str, "\"")))
        shift_str_left(str, get_idx_from_addr(str, addr), 1);
    while ((addr = my_strstr(str, "'")))
        shift_str_left(str, get_idx_from_addr(str, addr), 1);
    return (0);
}