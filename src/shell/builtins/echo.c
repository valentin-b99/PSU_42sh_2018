/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int char_in_list(char c, char *list_char)
{
    for (int i = 0; list_char[i]; i++)
        if (list_char[i] == c)
            return (1);
    return (0);
}

char *echo_tab_to_str(char **tab, char *str)
{
    for (int i = 0; tab[i]; i++) {
        if (i > 0)
            str = my_mstrcat(str, " ");
        str = my_mstrcat(str, tab[i]);
    }
    return (str);
}

int echo_error(shell_t *ft, char ***tab, int *new_line)
{
    *tab += 1;
    if (!(*tab)[0]) {
        my_putchar('\n');
        ft->rc = 1;
        return (84);
    }
    if (!my_strcmp((*tab)[0], "-n")) {
        *new_line = 0;
        *tab += 1;
    }
    if (!(*tab)[0]) {
        new_line ? my_putchar('\n') : 0;
        ft->rc = 1;
        return (84);
    }
    return (0);
}

char *replace_backslash(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (!my_strncmp(str + i, "\\0", 2))
            str = my_strnncat(i, i + 2, str, "\0");
        if (!my_strncmp(str + i, "\\a", 2))
            str = my_strnncat(i, i + 2, str, "\a");
        if (!my_strncmp(str + i, "\\b", 2))
            str = my_strnncat(i, i + 2, str, "\b");
        if (!my_strncmp(str + i, "\\t", 2))
            str = my_strnncat(i, i + 2, str, "\t");
        if (!my_strncmp(str + i, "\\n", 2))
            str = my_strnncat(i, i + 2, str, "\n");
        if (!my_strncmp(str + i, "\\v", 2))
            str = my_strnncat(i, i + 2, str, "\v");
        if (!my_strncmp(str + i, "\\r", 2))
            str = my_strnncat(i, i + 2, str, "\r");
    }
    return (str);
}

int my_echo(shell_t *ft, char **tab)
{
    int new_line = 1;
    char *str = NULL;

    if (echo_error(ft, &tab, &new_line))
        return (84);
    str = echo_tab_to_str(tab, str);
    str = replace_backslash(str);
    if (str) {
        my_putstr(str);
        ft->rc = 0;
    }
    if (str && new_line)
        my_putchar('\n');
    free(str);
    return (0);
}