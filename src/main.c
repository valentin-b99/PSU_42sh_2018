/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../include/my.h"
#include "../include/mysh.h"

int init_struct(shell_t *ft)
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
    display_prompt(ft);
    return (0);
}

int epure_parenthesis_tree(tree_t *leaf)
{
    char **cmd = NULL;

    if (leaf)
        cmd = my_str_to_wordtab(leaf->name, (char*[]){ " ", "\t", NULL });
    if (!leaf)
        return (84);
    if (leaf->name && check_if_parenthesis(leaf->name) == 1 &&
        leaf->if_each_check == 0 && my_strcmp(cmd[0], "if"))
        leaf->name = strtwt_epur_str(leaf->name, (char*[]){"(", ")", NULL}, 1);
    epure_parenthesis_tree(leaf->left);
    epure_parenthesis_tree(leaf->right);
    free_array(cmd);
    return (0);
}

int init_tree(shell_t *ft)
{
    if (my_str_istabspace(ft->input) == 1 || ft->input[0] == '\0' ||
        parse_input(ft, ft->tree) == 84) {
        return (rint_free(ft->input) | 84);
    }
    inorder(ft, ft->tree);
    epure_parenthesis_tree(ft->tree);
    if (found_tree_errors(ft, ft->tree) == 84) {
        free_tree(ft->tree);
        return (84);
    }
    return (0);
}

int init_vars(shell_t *ft)
{
    ft->rc = 0;
    ft->env = NULL;
    ft->tab = NULL;
    ft->alias = NULL;
    ft->fcd = 1;
    ft->old_fd = 0;
    ft->right_redir = 0;
    ft->left_redir = 0;
    return (0);
}

int main(__attribute__ ((unused)) int ac, __attribute__ ((unused)) char **av,
    char **env)
{
    shell_t ft;

    init_vars(&ft);
    env_to_ll(&ft, env);
    if (ac > 1)
        return (scripting(av[1], &ft));
    mysh(&ft);
    return (0);
}
