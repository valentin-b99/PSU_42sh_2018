/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int nb_charac(char *str, char c)
{
    int i = -1;
    int count = 0;

    while (str[++i])
        if (str[i] == c)
            count++;
    return (count);
}

char **str_to_tab_with_double_quote(char *str, char **delims, shell_t *ft)
{
    char *epur = strtwt_epur_str(str, delims, 0);
    int i = -1;
    int profondeur = 0;
    int k = -1;
    char tmp[1000];
    int h = -1;
    char **ret = malloc(sizeof(char *) * (epur ? my_strlen(epur) : 0));

    if (!epur || nb_charac(epur, '"') % 2) {
        my_printf("Unmatched '\"'.\n");
        ft->rc = 1;
        return (NULL);
    }
    while (epur[++i]) {
        for (int j = 0; delims[j]; j++) {
            if (strstr(epur + i, delims[j]) == epur + i && !profondeur) {
                tmp[++h] = 0;
                ret[++k] = my_strdup(tmp);
                h = -1;
                i++;
            }
        }
        if (epur[i] && epur[i] == '"') {
            profondeur = profondeur == 1 ? 0 : 1;
        } else
            if (i - 1 >= 0 && epur[i - 1] == '\\' && !profondeur)
                tmp[h] = epur[i];
            else
                tmp[++h] = epur[i];
    }
    tmp[++h] = 0;
    ret[++k] = my_strdup(tmp);
    ret[++k] = NULL;
    free(epur);
    return (ret);
}

int check_or_and_operators(tree_t *leaf)
{
    if (!my_strcmp(leaf->name, "&&")) {
        if (leaf->left->return_val == 0)
            return (0);
        return (1);
    }
    if (!my_strcmp(leaf->name, "||")) {
        if (leaf->left->return_val == 0)
            return (1);
    }
    return (0);
}

int check_parent_redir(shell_t *ft, tree_t *leaf)
{
    if ((my_strcmp(leaf->name, ">") == 0) ||
        (my_strcmp(leaf->name, ">>") == 0)) {
        right_side(ft, leaf->right->name, leaf);
        leaf->right->check = 1;
    }
    if ((my_strcmp(leaf->name, "<") == 0) ||
        (my_strcmp(leaf->name, "<<") == 0)) {
        left_side(ft, leaf->right->name, leaf);
        leaf->right->check = 1;
    }
    return (0);
}
