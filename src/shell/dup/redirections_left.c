/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int left_side(shell_t *ft, char *file, tree_t *leaf)
{
    int fd = 0;
    int j = !my_strcmp(leaf->name, "<") ? 1 : 2;

    if (j == 1) {
        check_if_already_redir(ft);
        fd = open(file, O_RDONLY);
        if (fd == -1) {
            my_printf("%s: No such file or directory.\n");
            leaf->left->check = 1;
            return (84);
        }
        ft->old_fd = dup(0);
        dup2(fd, 0);
        close(fd);
        ft->left_redir = 1;
    }
    else if (j == 2)
        double_left_redir(ft, file);
    return (0);
}

int double_left_redir_end(shell_t *ft, char *target)
{
    int fd = 0;

    fd = open(target, O_RDONLY);
    ft->old_fd = dup(0);
    dup2(fd, 0);
    close(fd);
    ft->left_redir = 1;
    return (0);
}

int double_left_redir(shell_t *ft, char *target)
{
    char *s = NULL;
    int fd = open(target, O_RDWR | O_CREAT, 0644);

    check_if_already_redir(ft);
    write(0, "? ", 2);
    while ((s = get_next_line(0))) {
        if (!s[0] || !my_strcmp(s, target))
            break;
        write(0, "? ", 2);
        write(fd, s, my_strlen(s));
        write(fd, "\n", 1);
    }
    free(s);
    double_left_redir_end(ft, target);
    return (0);
}
