/*
** EPITECH PROJECT, 2018
** my_printf_tmp3
** File description:
** my_printf_tmp3
*/

#include "../my.h"

int is_opt_flag(char c)
{
    char *flags = "#0- +";
    int i = 0;

    while (flags[i]) {
        if (c == flags[i])
            return (i);
        ++i;
    }
    return (-1);
}

int is_req_flag(char c)
{
    char *flags = "diouxXcsSpb%";
    int i = 0;

    while (flags[i]) {
        if (c == flags[i])
            return (i);
        ++i;
    }
    return (-1);
}

int get_opt_flags(int i, char *str, prtf_t *ft)
{
    ft->oflags = x_memset(0, 2, sizeof(char));

    while (is_opt_flag(str[i]) != -1) {
        ft->oflags = my_realloc(ft->oflags, my_strlen(ft->oflags) + 1);
        ft->oflags[my_strlen(ft->oflags)] = str[i];
        ++i;
    }
    return (i);
}

int get_req_flags(int i, char *str, prtf_t *ft)
{
    int tmp = i;
    int pos = -1;

    while (is_opt_flag(str[i]) != -1 || (str[i] >= '0' && str[i] <= '9')
        || str[i] == '.')
        ++i;
    if ((pos = is_req_flag(str[i])) == -1) {
        ft->rflag = -1;
        return (tmp - 1);
    }
    else {
        ft->rflag = pos;
        return (i + 1);
    }
    return (0);
}

int my_str_contains(char *str, char c)
{
    int i = -1;

    while (str[++i] && str[i] != c);
    if (!str[i])
        return (0);
    return (1);
}