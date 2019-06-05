/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

char **create_tab_for_exec(tree_t *leaf, int check, shell_t *ft)
{
    char **cmd_left = NULL;
    char **cmd_right = NULL;

    if (check == 0) {
        cmd_left = leaf->left && found_if_just_separator(leaf->left->name) == 0
        && leaf->left->check == 0 ?
        str_to_tab_with_double_quote(leaf->left->name, (char*[]){" ", NULL }, ft) : 0;
        return (cmd_left);
    }
    if (check == 1) {
        cmd_right = leaf->right &&
        found_if_just_separator(leaf->right->name) == 0
        && leaf->right->check == 0 ?
            str_to_tab_with_double_quote(leaf->right->name, (char*[]){" ", NULL }, ft) : 0;
        return (cmd_right);
    }
    return (NULL);
}

int my_exec(shell_t *ft, tree_t *leaf)
{
    char **cmd_left = create_tab_for_exec(leaf, 0, ft);
    char **cmd_right = create_tab_for_exec(leaf, 1, ft);
    int turn = 0;

    for (int i = 0 ; i < (leaf->left && leaf->right ? 2 : 1) ; i++) {
        if ((is_builtin((turn == 0 ? cmd_left : cmd_right), ft)) != -1);
        else
            get_access_and_fork(ft, turn == 0 ? cmd_left : cmd_right);
        turn == 0 ? leaf->left->return_val = ft->rc : 0;
        turn == 1 ? leaf->right->return_val = ft->rc : 0;
        turn = turn == 0 ? 1 : 0;
        if (check_or_and_operators(leaf) == 1)
            break;
    }
    clean_redir(ft, leaf);
    if (cmd_left)
        leaf->left->check = 1;
    if (cmd_right)
        leaf->right->check = 1;
    return (free_array(cmd_left) | free_array(cmd_right) | 0);
}

void is_operator(shell_t *ft, tree_t *leaf)
{
    char *op[] = { ";", "&&", "||", "|", "<<", "<", ">>", ">", NULL };

    for (int i = 0; op[i]; ++i)
        if (my_strcmp(op[i], leaf->name) == 0) {
            leaf->left->name ? my_exec(ft, leaf) : 0;
        }
}

int cmd(shell_t *ft, tree_t *leaf)
{
    char *path = NULL;

    if(!(path = ll_find(ft->env, "PATH")))
        ll_update_node(ft, &ft->env, "PATH",
        "/usr/local/bin/:/usr/bin/:/bin/");
    free(path);
    if (my_strcmp(leaf->parent->name, "|") == 0)
        my_exec_pipe(ft, leaf);
    else
        is_operator(ft, leaf->parent);
    return (0);
}

int exec_command(shell_t *ft, tree_t *leaf)
{
    static int save_in = -1;
    static int save_out = -1;

    set_saves_pipes(leaf, &save_in, &save_out);
    if (!leaf)
        return (0);
    check_parent_redir(ft, leaf);
    if (my_strcmp(leaf->name, "|") == 0)
        return (pipe_function(ft, leaf, save_in, save_out));
    if (found_if_just_separator(leaf->name) == 0 && leaf->check == 0)
        cmd(ft, leaf);
    if (leaf->left)
        exec_command(ft, leaf->left);
    if (!my_strcmp(leaf->name, "&&") && !leaf->left->return_val && leaf->right)
        return (exec_command(ft, leaf->right));
    if (!my_strcmp(leaf->name, "||") && leaf->left->return_val && leaf->right)
        return (exec_command(ft, leaf->right));
    if (leaf->right)
        exec_command(ft, leaf->right);
    return (0);
}
