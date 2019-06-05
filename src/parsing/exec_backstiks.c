/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** exec_backsticks
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

void init_exec_backstick(shell_t *new)
{
    new->rc = 0;
    new->env = NULL;
    new->tab = NULL;
    new->alias = NULL;
    new->fcd = 1;
    new->right_redir = 0;
    new->left_redir = 0;
    new->old_fd = 0;
    new->tree = NULL;
    new->tree = NULL;
    new->input = NULL;
    new->esc_input = NULL;
    new->left = NULL;
    new->right = NULL;
    new->input = NULL;
    new->prio = 0;
    new->empty = 0;
    new->fail = 0;
    new->alias_check = 0;
    new->if_check = 0;
}

void exec_str(shell_t *new, char *cmd, shell_t *ft)
{
    new->env = ft->env;
    init_exec_backstick(new);
    if (new->old_fd != 0) {
        (new->right_redir == 1 ? dup2(new->old_fd, 1) : dup2(new->old_fd, 0));
        close(new->old_fd);
        new->right_redir = 0;
        new->left_redir = 0;
        new->old_fd = 0;
    }
    get_ft(new);
    inhibitors(new, my_strdup(cmd));
    if (init_tree(new) == 84)
        return;
    exec_command(new, new->tree);
    free(new->input);
    free(new->esc_input);
    free_tree(new->tree);
    free(new);
    get_ft(ft);
}

char *exec_backsticks(shell_t *ft, char *cmd)
{
    char *ret = NULL;
    char *tmp = NULL;
    int pfd[2];
    int save_in = dup(1);
    shell_t *tf = malloc(sizeof(shell_t));

    if (pipe(pfd))
        return (NULL);
    dup2(pfd[1], 1);
    exec_str(tf, cmd, ft);
    dup2(save_in, 1);
    close(pfd[1]);
    while ((tmp = get_next_line(pfd[0]))) {
        ret = newcat(ret, tmp);
        ret = newcat(ret, " ");
        free(tmp);
    }
    close(pfd[0]);
    return (ret);
}