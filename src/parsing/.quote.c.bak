/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int count_quote(shell_t *ft)
{
    int count = 0;

    for (int i = 0; ft->input[i] != '\0'; i++)
        if (ft->input[i] == '"')
            count += 1;
    return (count);
}

int found_close_quote(shell_t *ft, int i)
{
    while (ft->input[i] != '\0') {
        if (ft->input[i] == '"') {
            return (i);
        }
        i++;
    }
    return (0);
}

int *found_where_ignore_quote(shell_t *ft)
{
    int count = (count_quote(ft) * 2);
    int *array = count == 0 ? NULL : malloc(sizeof(int) * (count + 1));
    int j = 0;
    int k = 1;
    int save = 0;

    if (!array)
        return (NULL);
    for (int i = 0; ft->input[i] != '\0'; i++) {
        if (ft->input[i] == '"' && save == 0) {
            array[j] = i;
            save = 1;
            j += 2;
            i++;
        }
        if (ft->input[i] == '"' && save == 1) {
            array[k] = i;
            k += 2;
            save = 0;
            i++;
        }
    }
    array[k - 1] = -1;
    return (array);
}

int epure_quote_tree(tree_t *leaf)
{
    char **cmd = NULL;

    if (leaf)
        cmd = my_str_to_wordtab(leaf->name, (char*[]){ " ", "\t", NULL });
    if (!leaf)
        return (84);
    if (leaf->name)
        leaf->name = strtwt_epur_str(leaf->name, (char*[]){"\"", NULL}, 1);
    epure_quote_tree(leaf->left);
    epure_quote_tree(leaf->right);
    free_array(cmd);
    return (0);
}
