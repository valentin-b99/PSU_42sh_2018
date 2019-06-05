/*
** EPITECH PROJECT, 2018
** my_printf_tmp
** File description:
** my_printf_tmp
*/

#include "../my.h"

int print_char(va_list ap, prtf_t *ft)
{
    int blanks = ft->width - 1;
    int ret = 0;

    if (blanks > 0) {
        for (int i = 0; i < blanks; ++i)
            ret += my_putchar(' ');
    }
    return (my_putchar(va_arg(ap, int)) + ret);
}

int print_str(va_list ap, prtf_t *ft)
{
    char *str = va_arg(ap, char *);
    int len = 0;
    int blanks = 0;
    int ret = 0;

    if (str == NULL) {
        write(1, "(null)", 6);
        return (6);
    }
    len = my_strlen(str);
    len = ft->has_precision && ft->precision < len ? ft->precision : len;
    if (ft->width > len) {
        blanks = ft->width - len;
        my_str_contains(ft->oflags, '-') ? write(1, str, len) : 0;
        for (int i = 0; i < blanks; ++i)
            ret += my_putchar(' ');
        my_str_contains(ft->oflags, '-') == 0 ? write(1, str, len) : 0;
    } else
        write(1, str, len);
    return (len + ret);
}

int print_str_octal(va_list ap, prtf_t *ft)
{
    (void)ft;
    return (my_showstr_octal(va_arg(ap, char *)));
}

int print_lower_hex(va_list ap, prtf_t *ft)
{
    int ret = 0;
    unsigned int nbr = va_arg(ap, unsigned int);
    char *tmp = x_memset(0, 22, sizeof(char));

    ret = my_printf_handle_numbers_p(&tmp, ft);
    if (my_str_contains(ft->oflags, '#') && nbr > 0) {
        write(1, "0x", 2);
        ret += 2;
    }
    free(tmp);
    return (my_putunbr_base(nbr, "0123456789abcdef", 0) + ret);
}

int print_upper_hex(va_list ap, prtf_t *ft)
{
    unsigned int nbr = va_arg(ap, unsigned int);

    if (my_str_contains(ft->oflags, '#') && nbr > 0) {
        write(1, "0X", 2);
    }
    return (my_putunbr_base(nbr, "0123456789ABCDEF", 0));
}