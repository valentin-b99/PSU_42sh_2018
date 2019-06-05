/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int parse_tree_str_two(char *ll_name, char *delim)
{
    int i = -1;

    while (ll_name[++i] != '\0')
        if (delim[0] == ll_name[i] && delim[1] == ll_name[i + 1])
            return (i);
    return (84);
}

int parse_tree_str_three(char *ll_name, char *delim)
{
    int i = -1;

    while (ll_name[++i] != '\0')
        if (delim[0] == ll_name[i])
            return (i);
    return (84);
}

int parse_tree_str(char *ll_name, int current, char *delim)
{
    if (current == 4 || current == 6 || current == 2 || current == 1)
        return (parse_tree_str_two(ll_name, delim));
    else
        return (parse_tree_str_three(ll_name, delim));
    return (84);
}
