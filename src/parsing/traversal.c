/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int check_redir(tree_t *leaf)
{
    char *ok[] = { ";", "||", "&&", "|", "<<", "<", ">>", ">", NULL };
    int j = 0;
    int i = 0;

    if (!leaf->name)
        return (84);
    while (ok[i] != NULL) {
        if ((j = parse_tree_str(leaf->name, i, ok[i])) != 84)
            break;
        i++;
    }
    if (!ok[i])
        return (84);
    if (leaf->hidden)
        if (leaf->hidden[j] != '0')
            return (84);
    if (found_if_just_separator(leaf->name) == 1)
        return (84);
    return (0);
}

int nb_quote(shell_t *ft)
{
    int i = 0;
    int count = 0;

    while (ft->input[i] != '\0') {
        if (ft->input[i] == '"')
            count ++;
        i++;
    }
    return (count);
}

int inorder(shell_t *ft, tree_t *leaf)
{
    tree_t *tmp = ft->tree;
    int *quote = found_where_ignore_quote(ft);

    if (!leaf)
        return (84);
    if (check_redir(leaf) == 0 && !leaf->if_each_check && quote == 0) {
        free(ft->input);
        ft->input = my_strdup(leaf->name);
        parse_input(ft, leaf);
        leaf = tmp;
    }
    inorder(ft, leaf->left);
    inorder(ft, leaf->right);
    return (0);
}

int found_if_just_separator(char *leaf_name)
{
    char *ok[] = { ";", "||", "&&", "|", "<<", "<", ">>", ">", NULL };
    int i = 0;

    if (!leaf_name)
        return (0);
    while (ok[i]) {
        if (my_strcmp(ok[i], leaf_name) == 0)
            return (1);
        i++;
    }
    return (0);
}
