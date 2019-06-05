/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int check_double_redir_errors(shell_t *ft, int i, tree_t *leaf, int check)
{
    char *ok[] = { ";", "||", "&&", "|", "<<", "<", ">>", ">", NULL };

    if (i >= 4 && i <= 7 && (check == 0 ? leaf->left->name : leaf->right->name)
    && my_strcmp(ok[i], check == 0 ?
    leaf->left->name : leaf->right->name) == 0) {
        ft->fail = 1;
        ft->rc = 1;
        if (i == 4 || i == 5)
            write(2, "Ambiguous input redirect.\n", 26);
        else
            write(2, "Ambiguous output redirect.\n", 27);
        return (84);
    }
    return (0);
}

int check_left_error(shell_t *ft, int i, tree_t *leaf)
{
    if (!leaf->left->name || !leaf->right || !leaf->right->name) {
        if (i >= 1 && i <= 3) {
            ft->fail = 1;
            ft->rc = 1;
            write(2, "Invalid null command.\n", 22);
            return (84);
        }
        if (i >= 4 && i <= 7) {
            ft->fail = 1;
            ft->rc = 1;
            write(2, "Missing name for redirect.\n", 27);
            return (84);
        }
    }
    return (0);
}

int check_right_error(shell_t *ft, int i, tree_t *leaf)
{
    if (!leaf->right->name || !leaf->left || !leaf->left->name) {
        if (i >= 0 && i <= 7) {
            ft->fail = 1;
            ft->rc = 1;
            write(2, "Invalid null command.\n", 22);
            return (84);
        }
    }
    return (0);
}

int check_double_way_errors(shell_t *ft, int i, tree_t *leaf)
{
    if ((found_if_just_separator(leaf->left->name) && !leaf->left->left)
    || (found_if_just_separator(leaf->right->name) && !leaf->right->right)) {
        if (i >= 1 && i <= 3) {
            ft->fail = 1;
            ft->rc = 1;
            write(2, "Invalid null command.\n", 22);
            return (84);
        }
        if (i >= 4 && i <= 7) {
            ft->rc = 1;
            ft->fail = 1;
            write(2, "Missing name for redirect.\n", 27);
            return (84);
        }
    }
    return (0);
}

int check_error_delim(shell_t *ft, int i, tree_t *leaf)
{
    if (ft->fail == 1 || (!leaf->left && !leaf->right))
        return (84);
    if (leaf->left && leaf->right) {
        if (check_double_way_errors(ft, i, leaf) == 84)
            return (84);
    }
    if (leaf->left) {
        if (check_left_error(ft, i, leaf) == 84)
            return (84);
        if (check_double_redir_errors(ft, i, leaf, 0) == 84)
            return (84);
    }
    if (leaf->right) {
        if (check_right_error(ft, i, leaf) == 84)
            return (84);
        if (check_double_redir_errors(ft, i, leaf, 1) == 84)
            return (84);
    }
    return (0);
}
