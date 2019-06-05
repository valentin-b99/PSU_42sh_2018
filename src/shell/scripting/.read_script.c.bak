/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** scripting
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

void init_script(shell_t *ft)
{
    ft->tree = NULL;
    ft->input = NULL;
    ft->esc_input = NULL;
    ft->left = NULL;
    ft->right = NULL;
    ft->input = NULL;
    ft->prio = 0;
    ft->empty = 0;
    ft->fail = 0;
    ft->alias_check = 0;
    ft->if_check = 0;
    if (ft->old_fd != 0) {
        (ft->right_redir == 1 ? dup2(ft->old_fd, 1) : dup2(ft->old_fd, 0));
        close(ft->old_fd);
        ft->right_redir = 0;
        ft->left_redir = 0;
        ft->old_fd = 0;
    }
}

int scripting(char *file, shell_t *ft)
{
    int fd = open(file, O_RDONLY);
    char *str;
    char *path = NULL;

    if (fd < 0) {
        my_printf("invalid script name : [%s]\n", file);
        return (84);
    }
    str = get_next_line(fd);
    while ((str = get_next_line(fd))) {
        init_script(ft);
        get_ft(ft);
        if (!str) {
            isatty(0) == 1 ? write(1, "exit\n", 5) : 0;
            exit(ll_free(ft->env) | ll_free_alias(ft->alias) | ft->rc);
        }
        backsticks(ft, &str);
        inhibitors(ft, str);
        replace_vars(ft, &ft->input);
        if (!ft->input || init_tree(ft) == 84)
            continue;
        exec_command(ft, ft->tree);
        free(ft->input);
        free(ft->esc_input);
        free_tree(ft->tree);
        free(path);
    }
    return (ft->rc);
}