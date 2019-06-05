/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int *found_where_ignore(shell_t *ft)
{
    int count = (count_open_parenthesis(ft) * 2);
    int *array = count == 0 ? NULL : malloc(sizeof(int) * (count + 1));
    int j = 0;
    int k = 1;

    if (!array)
        return (NULL);
    for (int i = 0; ft->input[i] != '\0'; i++)
        if (ft->input[i] == '(') {
            array[j] = i;
            j += 2;
            array[k] = found_good_close_parenthesis(ft, i + 1);
            k += 2;
        }
    array[k - 1] = -1;
    return (array);
}

int check_parenthesis(shell_t *ft)
{
    int open = 0;
    int close = 0;
    int i = -1;

    while (ft->input[++i] != '\0')
        if (ft->input[i] == '(' || ft->input[i] == ')')
            ft->input[i] == '(' ? open++ : close++;
    if (open > close || close > open) {
        open > close ?
        write(1, "Too many ('s.\n", 14) : write(1, "Too many )'s.\n", 14);
        ft->rc = 1;
        return (84);
    }
    return (0);
}
