/*
** EPITECH PROJECT, 2019
** pipes
** File description:
** pipes
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

void my_exec_pipe(shell_t *ft, tree_t *leaf)
{
    char **cmd_arr = my_str_to_wordtab(leaf->name,
        (char*[]){ " ", "\t", NULL });

    if ((is_builtin(cmd_arr, ft)) == -1)
        get_access_and_fork(ft, cmd_arr);
    clean_redir(ft, leaf);
    leaf->check = 1;
}

void pipe_function_exec(shell_t *ft, tree_t *leaf)
{
    int pfd[2];

    if (pipe(pfd))
        exit(84);
    if (fork() == 0) {
        dup2(pfd[1], 1);
        close(pfd[0]);
        if (leaf->left)
            exec_command(ft, leaf->left);
        close(pfd[1]);
        exit(0);
    }
    dup2(pfd[0], 0);
    close(pfd[1]);
    close(pfd[0]);
}

int pipe_function(shell_t *ft, tree_t *leaf, int save_in, int save_out)
{
    pipe_function_exec(ft, leaf);
    if (leaf->right)
        exec_command(ft, leaf->right);
    if (!my_strcmp(leaf->name, "|") && my_strcmp(leaf->right->name, "|")) {
        dup2(save_out, 1);
        close(save_out);
        dup2(save_in, 0);
        close(save_in);
    }
    return (0);
}

void set_saves_pipes(tree_t *leaf, int *save_in, int *save_out)
{
    if (!my_strcmp(leaf->name, "|") &&
    (!leaf->parent || my_strcmp(leaf->parent->name, "|"))) {
        *save_in = dup(0);
        *save_out = dup(1);
    }
}