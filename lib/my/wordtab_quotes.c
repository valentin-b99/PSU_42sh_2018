/*
** EPITECH PROJECT, 2019
** wordtab_quotes
** File description:
** wordtab_quotes
*/

#include "./my.h"

int wq_free_tab(char **tab)
{
    for (int i = 0; tab && tab[i] != NULL; ++i)
        free(tab[i]);
    tab ? free(tab) : 0;
    return (0);
}

int wq_is_delim(char *str, char **delims, int mode)
{
    int index = mode ? 0 : -1;
    int len = 0;

    for (int i = 0; !mode && delims[i]; ++i) {
        if (my_strncmp(str, delims[i], my_strlen(delims[i])) == 0) {
            len < my_strlen(delims[i]) ? index = i : 0;
            len < my_strlen(delims[i]) ? len = my_strlen(delims[i]) : 0;
        }
    }
    for (char *tmp = mode ? delims[0] : NULL; tmp && tmp >= str; --tmp) {
        len += *tmp == '"' || *tmp == '\'' ? 1 : 0;
        if (len == 1 && (mode = *tmp))
            break;
    }
    for (char *tmp = mode ? delims[0] : NULL; tmp && *tmp; ++tmp, ++index) {
        len += *tmp == mode ? 1 : 0;
        if (!len || len == 2)
            break;
    }
    return (len == 2 ? index + 1 : index);
}

int wq_keep_quotes(char *str, char *res, int *i, int mode)
{
    char c = 0;

    if (!mode) {
        c = str[i[0]];
        res[i[1]++] = str[i[0]++];
        while (str[i[0]] && str[i[0]] != c)
            res[i[1]++] = str[i[0]++];
        res[i[1]++] = str[i[0]++];
    } else if (mode == 1) {
        for (int j = 0; str[j]; ++j) {
            c = !c && (str[j] == '"' || str[j] == '\'') ? str[j] : c;
            i[2] += str[j] == c ? 1 : 0;
            i[0] += (str[j] == ' ' && i[2] == -1) || i[2] == 2 ? 1 : 0;
            c = i[2] == 2 ? 0 : c;
            i[2] = i[2] == 2 ? -1 : i[2];
        }
    }
    return (0);
}

/*
** i[0] - > i
** i[1] -> j
** i[2] -> index
** i[3] -> space_placed
*/
char *wq_epur_str(char *str, char **delims, int free_str)
{
    char *res = str && my_strlen(str) ?
        x_memset(0, my_strlen(str) + 1, sizeof(char)) : NULL;
    int i[4] = { 0, 0, 0, 0 };

    if (!str || !my_strlen(str))
        return (NULL);
    while (str[i[0]] && !(i[3] = 0)) {
        while (str[i[0]] && (i[2] = wq_is_delim(&str[i[0]], delims, 0)) >= 0) {
            i[0] += my_strlen(delims[i[2]]);
            i[1] && !i[3] ? res[i[1]++] = ' ' : 0;
            i[1] && !i[3] ? i[3] = 1 : 0;
        }
        if (str[i[0]] == '"' || str[i[0]] == '\'')
            wq_keep_quotes(str, res, i, 0);
        str[i[0]] ? res[i[1]++] = str[i[0]++] : 0;
    }
    for (int i = my_strlen(res) - 1; i >= 0 && res[i] == ' '; --i)
        res[i] = 0;
    free_str ? free(str) : 0;
    return (res);
}

/*
** arr[0] -> elems
** arr[1] -> epur index
** arr[2] -> quotes_count
*/
char **wordtab_quotes(char *str, char **delims)
{
    char *epur = wq_epur_str(str, delims, 0);
    char **res = NULL;
    int arr[3] = { 0, 0, -1 };
    char *tmp = NULL;

    if (!str || !epur)
        return (NULL);
    wq_keep_quotes(epur, NULL, arr, 1);
    if (!(res = malloc(sizeof(char *) * (arr[0] + 2))))
        return (NULL);
    for (int i = 0; i <= arr[0]; ++i) {
        res[i] = my_strdup(&epur[arr[1]]);
        if ((tmp = my_strstr(res[i], " ")))
            *(tmp + wq_is_delim(res[i], &tmp, 1)) = 0;
        arr[1] += my_strlen(res[i]) + 1;
    }
    res[arr[0] + 1] = NULL;
    free(epur);
    return (res);
}