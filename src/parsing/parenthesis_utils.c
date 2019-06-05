/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int check_if_parenthesis(char *str)
{
    int i = 0;

    while (str[i]) {
        if (str[i] == '(' || str[i] == ')')
            return (1);
        i++;
    }
    return (0);
}

int found_last_open_parenthesis(shell_t *ft)
{
    int i = 0;
    int start = 0;

    while (ft->input[i] != '\0') {
        if (ft->input[i] == '(') {
            start = i;
            break;
        }
        i++;
    }
    return (start);
}

int count_open_parenthesis(shell_t *ft)
{
    int count = 0;

    for (int i = 0; ft->input[i] != '\0'; i++)
        if (ft->input[i] == '(')
            count += 1;
    return (count);
}

int found_good_close_parenthesis(shell_t *ft, int i)
{
    int parenthesis_left = 0;

    while (ft->input[i] != '\0') {
        ft->input[i] == '(' ? parenthesis_left += 1 : 0;
        if (ft->input[i] == ')') {
            if (parenthesis_left == 0)
                return (i);
            parenthesis_left--;
        }
        i++;
    }
    return (0);
}
