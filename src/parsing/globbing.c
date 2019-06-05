/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** globbing
*/

#include "../../include/my.h"
#include "../../include/mysh.h"

int contains(char *str, char *proc)
{
    for (int i = 0; str[i]; i++) {
        for (int j = 0; proc[j]; j++) {
            if (str[i] == proc[j] && my_strcmp(str, "[") &&
                my_strcmp(str, "]"))
                return (1);
        }
    }
    return (0);
}

int check_str(char *str)
{
    int i = -1;

    if (!str)
        return (1);
    while (str[++i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'));
    if (!str[i])
        return (1);
    return (0);
}

int call_glob(int *nb, char **str, glob_t *paths)
{
    if (glob(*str, GLOB_NOCHECK | GLOB_NOSORT, NULL, paths )) {
        my_printf("glob failed\n");
        return (1);
    } else {
        if (paths->gl_pathc >= 1 && my_strcmp(paths->gl_pathv[0], *str))
            *nb = *nb + 1;
        if (!my_strcmp(paths->gl_pathv[0], *str)) {
            free(paths->gl_pathv[0]);
            paths->gl_pathv[0] = my_strdup(" ");
        }
        free(*str);
        *str = tab_to_str(paths->gl_pathv);
    }
    return (0);
}

char *free_return_glob(char *str, char **tab, int nb, int match)
{
    str = tab_to_str(tab);
    free_array(tab);
    if (!nb && match) {
        free(str);
        my_printf("%s:  No match.");
        str = NULL;
    }
    return (str);
}

char *check_glob(char *str)
{
    char **tab = my_str_to_wordtab(check_str(str) ? "" : str,
        (char *[]){ " ", "\t", NULL });
    glob_t paths;
    int nb = 0;
    int match = 0;
    int ret = 0;

    paths.gl_pathc = 0;
    paths.gl_pathv = NULL;
    paths.gl_offs = 0;
    if (!str || check_str(str) || !tab)
        return (NULL);
    for (int i = 0; tab[i]; i++) {
        if (contains(tab[i], "*?[]") && !my_strstr(tab[i], "$?")) {
            ret = call_glob(&nb, &tab[i], &paths);
            match++;
        }
        if (ret)
            break;
    }
    return (free_return_glob(str, tab, nb, match));
}