/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int right_side(shell_t *ft, char *file, tree_t *leaf)
{
    int fd = 0;
    int j = !my_strcmp(leaf->name, ">") ? 1 : 2;

    check_if_already_redir(ft);
    ft->right_redir = 1;
    fd = open(file, O_RDWR | O_CREAT
    | (j == 2 ? O_APPEND : 0), 0644);
    ft->old_fd = dup(1);
    dup2(fd, 1);
    close(fd);
    return (0);
}
