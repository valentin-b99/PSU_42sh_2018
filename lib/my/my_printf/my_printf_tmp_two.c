/*
** EPITECH PROJECT, 2018
** my_printf_tmp2
** File description:
** my_printf_tmp2
*/

#include "../my.h"

int print_nbr(va_list ap, prtf_t *ft)
{
    int nbr = va_arg(ap, int);
    char *tmp = x_memset(0, 22, sizeof(char));
    int ret = 0;

    tmp = my_ltoa_base(nbr, tmp, "0123456789", 0);
    ret = my_printf_handle_numbers_p(&tmp, ft);
    if ((MSC(ft->oflags, ' ') || MSC(ft->oflags, '+')) && nbr >= 0) {
        if (my_str_contains(ft->oflags, '+')) {
            ret += write(1, "+", 1);
            write(1, tmp, my_strlen(tmp));
        } else {
            ret += write(1, " ", 1);
            ret += write(1, tmp, my_strlen(tmp));
        }
    } else
        write(1, tmp, my_strlen(tmp));
    free(tmp);
    return (ret);
}

int print_long_base(va_list ap, prtf_t *ft)
{
    (void)ft;
    write(1, "0x", 2);
    return (my_putlong_base(va_arg(ap, long), "0123456789abcdef", 0) + 2);
}

int print_binary(va_list ap, prtf_t *ft)
{
    (void)ft;
    return (my_putnbr_base(va_arg(ap, int), "01", 0));
}

int print_unbr_octal(va_list ap, prtf_t *ft)
{
    int i = 0;
    unsigned int nbr = va_arg(ap, unsigned int);

    if (my_str_contains(ft->oflags, '#') && nbr > 0) {
        write(1, "0", 1);
        i = 1;
    }
    return (my_putunbr_base(nbr, "01234567", 0) + i);
}

int print_unbr_decimal(va_list ap, prtf_t *ft)
{
    (void)ft;
    return (my_putunbr_base(va_arg(ap, unsigned int), "0123456789", 0));
}