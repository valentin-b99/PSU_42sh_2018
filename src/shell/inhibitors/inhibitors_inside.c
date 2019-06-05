/*
** EPITECH PROJECT, 2019
** inhibitors_inside
** File description:
** inhibitors_inside
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

shell_t *get_ft(shell_t *ft)
{
    static shell_t *ret = NULL;

    if (ft)
        ret = ft;
    return (ret);
}

char *inhibitor_mask(shell_t *ft, char *str)
{
    char *res = x_memset(0, my_strlen(str) + 1, sizeof(char));
    int idx = 0;
    char *add = my_strstr(ft->input, str);

    if (!res || !add)
        return (NULL);
    for (char *tmp = ft->input; tmp != add; ++tmp, ++idx);
    for (int i = 0; str[i]; ++i)
        res[i] = ft->esc_input[idx++];
    return (res);
}

int shift_str_left(char *str, int idx, int times)
{
    for (int i = 0; i < times; ++i) {
        for (int j = idx; str[j]; ++j)
            str[j] = str[j + 1];
    }
    return (0);
}

int inhibitors_inside(shell_t *ft)
{
    ft->esc_input = x_memset(0, my_strlen(ft->input) + 1, sizeof(char));
    char *esc[] = { "\\", ";", ">", "<", "&", "|", "(", ")", NULL };

    for (int i = 0; ft->input[i]; ++i)
        ft->esc_input[i] = '0';
    for (int i = 0; ft->input[i]; ++i) {
        if (ft->esc_input[i] == '0' && ft->input[i] == '\\' &&
            my_tab_contains_char(esc, ft->input[i + 1])) {
            shift_str_left(ft->input, i, 1);
            ft->esc_input[i] = '1';
            i -= 1;
        }
    }
    return (0);
}
