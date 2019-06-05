/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

var_t *find_ll_variables(shell_t *ft, char *var)
{
    char *dif = NULL;

    for (var_t *tmp = ft->var; tmp; tmp = tmp->next) {
        if (!(dif = x_memset(0, my_strlen(tmp->name) + 2, sizeof(char))))
            return (NULL);
        my_strcat(dif, "$");
        my_strcat(dif, tmp->name);
        if (my_strcmp(dif, var) == 0)
            return (tmp);
        if (my_strcmp(tmp->name, var) == 0 && tmp->k == 0) {
            free(dif);
            return (NULL);
        }
        free(dif);
    }
    return (NULL);
}

int is_good_var(shell_t *ft, char **var)
{
    if (my_str_isnum(var[1]) == 1)
        return (84);
    find_same_variables(ft, var[1]);
    ft->variables[0] = my_strdup(var[1]);
    if (my_str_isnum(var[2]) == 1) {
        ft->variables[1] = my_strdup(var[2]);
        ft->variables[2] = NULL;
        return (0);
    }
    ft->variables[2] = my_strdup(var[2]);
    return (0);
}

int get_str_cote(char **dc)
{
    for (int i = 0; dc[i]; i += 1) {
        if (dc[i][0] == '"')
            remove_cote(dc[i]);
    }
    return (0);
}

int my_set_var(shell_t *ft, char **tab)
{
    char *buff = tab_to_str(tab);
    char **var = my_str_to_wordtab(tab[1], (char *[]){ "=", NULL });
    char **dc = wordtab_quotes(buff, (char *[]){ " ", "\t", "=", NULL });

    get_str_cote(dc);
    find_same_variables(ft, dc[1]);
    is_good_var(ft, dc);
    save_variables(ft);
    free(buff);
    return (strtwt_free_tab(var) | 0);
}
