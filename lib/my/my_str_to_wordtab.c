/*
** EPITECH PROJECT, 2019
** my_str_to_wordtab
** File description:
** my_str_to_wordtab
*/

#include "./my.h"

int strtwt_free_tab(char **tab)
{
    for (int i = 0; tab && tab[i] != NULL; ++i)
        free(tab[i]);
    tab ? free(tab) : 0;
    return (0);
}

int strtwt_is_delim(char *str, char **delims)
{
    int index = -1;
    int len = 0;

    for (int i = 0; delims[i]; ++i) {
        if (my_strncmp(str, delims[i], my_strlen(delims[i])) == 0) {
            len < my_strlen(delims[i]) ? index = i : 0;
            len < my_strlen(delims[i]) ? len = my_strlen(delims[i]) : 0;
        }
    }
    return (index);
}

/*
** i[0] - > i
** i[1] -> j
** i[2] -> index
** i[3] -> space_placed
*/
char *strtwt_epur_str(char *str, char **delims, int free_str)
{
    char *res = str && my_strlen(str) ?
        x_memset(0, my_strlen(str) + 1, sizeof(char)) : NULL;
    int i[4] = { 0, 0, 0, 0 };

    if (!str || !my_strlen(str))
        return (NULL);
    while (str[i[0]]) {
        while (str[i[0]] && (i[2] = strtwt_is_delim(&str[i[0]], delims)) >= 0) {
            i[0] += my_strlen(delims[i[2]]);
            i[1] && !i[3] ? res[i[1]++] = ' ' : 0;
            i[1] && !i[3] ? i[3] = 1 : 0;
        }
        str[i[0]] ? res[i[1]++] = str[i[0]++] : 0;
        i[3] = 0;
    }
    for (int i = my_strlen(res) - 1; i >= 0 && res[i] == ' '; --i)
        res[i] = 0;
    free_str ? free(str) : 0;
    return (res);
}

/*
** arr[0] -> elems
** arr[1] -> epur index
*/
char **my_str_to_wordtab(char *str, char **delims)
{
    char *epur = strtwt_epur_str(str, delims, 0);
    char **res = NULL;
    int arr[2] = { 0, 0 };

    if (!str || !epur)
        return (NULL);
    for (int i = 0; epur[i]; ++i)
        arr[0] += epur[i] == ' ' ? 1 : 0;
    if (!(res = malloc(sizeof(char *) * (arr[0] + 2))))
        return (NULL);
    for (int i = 0; i <= arr[0]; ++i) {
        res[i] = my_strdup(&epur[arr[1]]);
        my_strstr(res[i], " ") ? *my_strstr(res[i], " ") = 0 : 0;
        arr[1] += my_strlen(res[i]) + 1;
    }
    res[arr[0] + 1] = NULL;
    free(epur);
    return (res);
}
