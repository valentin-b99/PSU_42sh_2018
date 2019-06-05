/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int analyse_command(shell_t *ft, tree_t *leaf)
{
    char *ok[] = { ";", "||", "&&", "|", "<<", "<", ">>", ">", NULL };
    int i = -1;

    if (leaf->left && found_if_just_separator(leaf->left->name) == 1)
        analyse_command(ft, leaf->left);
    if (leaf->right && found_if_just_separator(leaf->right->name) == 1)
        analyse_command(ft, leaf->right);
    if (ft->fail == 1)
        return (84);
    while (ok[++i])
        if (!leaf->name || my_strcmp(ok[i], leaf->name) == 0)
            break;
    if (!ok[i] || check_error_delim(ft, i, leaf) == 84)
        return (84);
    return (0);
}

int found_tree_errors(shell_t *ft, tree_t *leaf)
{
    if (!leaf)
        return (0);
    if (!leaf->left && !leaf->right && my_strcmp(leaf->name, "|") == 0) {
        write(2, "Invalid null command.\n", 22);
        ft->rc = 1;
        return (84);
    }
    if (analyse_command(ft, leaf) == 84)
        return (84);
    if (leaf->left)
        found_tree_errors(ft, leaf->left);
    if (leaf->right)
        found_tree_errors(ft, leaf->right);
    return (0);
}
