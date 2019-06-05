/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int assign_left_right(shell_t *ft, int i, int check)
{
    int len = my_strlen(ft->input);
    char *ok[] = { ";", "||", "&&", "|", "<<", "<", ">>", ">", NULL };
    char *save = my_strdup(ft->input);

    ft->input = strtwt_epur_str(ft->input, (char*[]){" ", "\t", NULL }, 1);
    if (strtwt_is_delim(ft->input, ok) != -1) {
        ft->left = NULL;
        ft->right = my_strcpy(ft->input, &ft->input[i + check]);
        return (rint_free(save) | 0);
    }
    free(ft->input);
    ft->input = my_strdup(save);
    free(save);
    if ((ft->left = malloc(sizeof(char) * (i + 1))) == NULL)
        return (84);
    my_strncpy(ft->left, ft->input, i);
    if (ft->left[0] != '\0')
        ft->left = strtwt_epur_str(ft->left, (char*[]){" ", "\t", NULL }, 1);
    if (!(ft->right = malloc(sizeof(char) * (ABS(len - i) + check))))
        return (84);
    ft->right = my_strcpy(ft->right, &ft->input[i + check]);
    if (ft->right[0] != '\0')
        ft->right = strtwt_epur_str(ft->right, (char*[]){" ", "\t", NULL }, 1);
    return (0);
}

int assign_str_branch(shell_t *ft, int i)
{
    int check = 1;
    char *ok[] = { ";", "||", "&&", "|", "<<", "<", ">>", ">", NULL };

    if (my_strlen(ok[ft->prio]) == 2)
        check = 2;
    if (ft->empty == 1) {
        ft->left = my_strdup(ft->input);
        ft->left = strtwt_epur_str(ft->left, (char*[]){" ", "\t", NULL }, 1);
        ft->right = NULL;
    } else
        assign_left_right(ft, i, check);
    return (0);
}
