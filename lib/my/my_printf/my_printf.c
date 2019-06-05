/*
** EPITECH PROJECT, 2018
** my_printf
** File description:
** my_printf
*/

#include "../my.h"

int print_percent(va_list ap, prtf_t *ft)
{
    (void)ap;
    (void)ft;
    my_putchar('%');
    return (1);
}

int error_check(prtf_t *ft, int i, char *str)
{
    int tmp = 0;
    char *tmp_str;
    int period = 0;

    for (int j = i; is_req_flag(str[j]) == -1; ++j)
        if (str[j] == '.')
            period += 1;
    tmp = get_opt_flags(i, str, ft);
    ft->width = my_strtol(str + tmp, &tmp_str);
    for (int j = tmp; is_req_flag(str[j]) == -1; ++j)
        if (str[j] == '#' || str[j] == '-' || str[j] == ' ' || str[j] == '+'
            || period > 1)
            return (i - 1);
    if (tmp_str[0] == '.') {
        ft->has_precision = 1;
        ft->precision = my_strtol(tmp_str + 1, &tmp_str);
    } else
        ft->has_precision = 0;
    return (i);
}

int parser(prtf_t *ft, int i, char *str, va_list ap)
{
    my_printf_func_arr func[12] = { &print_nbr, &print_nbr, &print_unbr_octal,
        &print_unbr_decimal, &print_lower_hex, &print_upper_hex, &print_char,
        &print_str, &print_str_octal, &print_long_base, &print_binary,
        &print_percent };
    if (error_check(ft, i, str) == i - 1)
        return (i - 1);
    i = get_req_flags(i, str, ft);
    if (ft->rflag > -1)
        ft->ret_val = func[ft->rflag](ap, ft);
    free(ft->oflags);
    return (i);
}

int my_printf(char *format, ...)
{
    va_list ap;
    prtf_t ft;
    int i = 0;

    va_start(ap, format);
    while (format[i] != '\0') {
        if (format[i] == '%') {
            i = parser(&ft, i + 1, format, ap);
            continue;
        }
        if (i < my_strlen(format))
            ft.ret_val += my_putchar(format[i]);
        else
            break;
        ++i;
    }
    va_end(ap);
    return (ft.ret_val);
}