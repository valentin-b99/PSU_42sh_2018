/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int check_need_ignore_it(int *array, int i)
{
    int j = 0;

    if (!array)
        return (1);
    while (array[j] != -1) {
        if ((i > array[j] && i < array[j + 1]))
            return (-1);
        j += 2;
    }
    return (1);
}

int parse_str_to_found(shell_t *ft, char *delim)
{
    int i = 0;
    int *array = found_where_ignore(ft);
    int *quote = found_where_ignore_quote(ft);
    int j = 0;
    int len = my_strlen(delim);

    while (ft->input[i]) {
        if (my_strncmp(&ft->input[i], delim, len) == 0) {
            if (ft->esc_input[i] != '0' && ft->input[i + 1] == '\0')
                return (rint_free(array) | rint_free(quote) | -1);
            if ((j = check_need_ignore_it(array, i)) == 1 && ft->esc_input[i] != '1'
                && (j = check_need_ignore_it(quote, i)) == 1)
                return (rint_free(array) | rint_free(quote) | i);
        }
        i++;
    }
    return (rint_free(array) | rint_free(quote) | -1);
}

int found_priorities(shell_t *ft)
{
    int j = 0;
    char *ok[] = { ";", "||", "&&", "|", "<<", "<", ">>", ">", NULL };
    int i = 0;
    int *array = found_where_ignore(ft);
    char **cmd = my_str_to_wordtab(ft->input, (char*[]){ " ", "\t", NULL });

    if (!my_strcmp(cmd[0], "if") || !my_strcmp(cmd[0], "foreach") ) {
        ft->if_check = 1;
        ft->empty = 1;
        ft->prio = 0;
        return (rint_free(array) | free_array(cmd) | ft->prio);
    }
    while (ok[i] != NULL) {
        if ((j = parse_str_to_found(ft, ok[i])) != -1)
            break;
        if (i + 1 == 8) {
            rint_free(array);
            array = found_where_ignore(ft);
            if (!array) {
                i = 8;
                break;
            }
            i = 0;
            ft->input[array[0]] = ' ';
            ft->input[array[1]] = ' ';
            continue;
        }
        i++;
    }
    if (!ok[i]) {
        ft->empty = 1;
        ft->prio = 0;
        return (rint_free(array) | free_array(cmd) | ft->prio);
    }
    ft->prio = i;
    return (rint_free(array) | free_array(cmd) | j);
}

char *assign_root(shell_t *ft, int i)
{
    int return_val = 0;
    char *ok[] = { ";", "||", "&&", "|", "<<", "<", ">>", ">", NULL };

    if (ft->prio == 0)
        return (";");
    return_val = strtwt_is_delim(&ft->input[i], ok);
    return (ok[return_val]);
}

int parse_input(shell_t *ft, tree_t *leaf)
{
    int i = 0;
    char *root = NULL;

    ft->empty = ft->empty == 1 ? 0 : 0;
    if (check_parenthesis(ft) == 84)
        return (84);
    i = found_priorities(ft);
    root = my_strdup(assign_root(ft, i));
    if (!leaf) {
        ft->tree = root_tree(root);
        leaf = ft->tree;
    }
    assign_str_branch(ft, i);
    add_leaf(leaf, ft->left, ft->right, root);
    return (rint_free(ft->left) | rint_free(ft->right) | rint_free(root) | 0);
}
