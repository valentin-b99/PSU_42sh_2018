/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int clean_redir_two(shell_t *ft, tree_t *leaf)
{
    if (my_strcmp(leaf->parent->name, ";") == 0 && ft->right_redir == 1) {
        dup2(ft->old_fd, 1);
        close(ft->old_fd);
        ft->right_redir = 0;
        ft->old_fd = 0;
    }
    return (0);
}

int clean_redir(shell_t *ft, tree_t *leaf)
{
    if (!leaf->parent)
        return (0);
    if (my_strcmp(leaf->parent->name, ">") == 0 ||
        my_strcmp(leaf->parent->name, ">>") == 0) {
        dup2(ft->old_fd, 1);
        close(ft->old_fd);
        ft->right_redir = 0;
        ft->old_fd = 0;
    }
    if (my_strcmp(leaf->parent->name, "<") == 0 ||
        my_strcmp(leaf->parent->name, "<<") == 0) {
        dup2(ft->old_fd, 0);
        close(ft->old_fd);
        ft->old_fd = 0;
        ft->left_redir = 0;
    }
    clean_redir_two(ft, leaf);
    return (0);
}

int check_if_already_redir(shell_t *ft)
{
    if (ft->left_redir == 1) {
        dup2(ft->old_fd, 0);
        close(ft->old_fd);
        ft->old_fd = 0;
        ft->left_redir = 0;
    }
    if (ft->right_redir == 1) {
        dup2(ft->old_fd, 1);
        close(ft->old_fd);
        ft->right_redir = 0;
        ft->old_fd = 0;
    }
    return (0);
}
