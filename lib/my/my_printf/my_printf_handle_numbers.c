/*
** EPITECH PROJECT, 2018
** my_printf_handle_numbers
** File description:
** my_printf_handle_numbers
*/

#include "../my.h"

int my_printf_handle_numbers_p(char **str, prtf_t *ft)
{
    int neg = (*str)[0] == '-' ? 1 : 0;
    int len = my_strlen(neg ? *str + 1 : *str);
    int zeroes = ft->precision - len;

    my_revstr(neg ? *str + 1 : *str);
    if (ft->has_precision && zeroes > 0) {
        for (int i = 0; i < zeroes; ++i) {
            *str = my_realloc(*str, len + (neg ? 2 : 1));
            (*str)[neg ? len + 1 : len] = '0';
            len += 1;
        }
    }
    my_revstr(neg ? *str + 1 : *str);
    return (neg ? len + 1 : len);
}