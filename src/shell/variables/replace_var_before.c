/*
** EPITECH PROJECT, 2019
** replace_var_before.c
** File description:
** replace_var_before
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int verif_chars_var(char *str)
{
    int i = 0;

    while (str[i] && str[i] != '}') {
        if (!char_in_list(str[i], LIST_ENV_CHAR)) {
            write(2, "Illegal variable name.\n", 23);
            return (84);
        }
        i++;
    }
    return (0);
}

void replace_vars_next(shell_t *ft, char **str, int *i)
{
    if ((*str)[*i] == '$' && char_in_list((*str)[*i + 1], LIST_ENV_CHAR)) {
        *str = find_var_and_replace(ft, *str, i, 0);
        return;
    }
    if ((*str)[*i] == '$' && (*str)[*i + 1] == '{') {
        if (verif_chars_var(*str + *i + 2))
            return;
        *str = find_var_and_replace(ft, *str, i, 1);
        return;
    }
    if (!my_strncmp(*str + *i, "$?", 1) || !my_strncmp(*str + *i, "${?}", 3)) {
        *str = my_strnncat(*i, *i + 2, *str, my_itoa(ft->rc));
        return;
    }
}

void replace_vars(shell_t *ft, char **str)
{
    for (int i = 0; *str && (*str)[i]; i++) {
        replace_vars_next(ft, str, &i);
        if (!(*str))
            ft->rc = 1;
    }
}