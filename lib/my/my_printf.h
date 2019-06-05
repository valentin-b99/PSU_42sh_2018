/*
** EPITECH PROJECT, 2018
** my_printf
** File description:
** my_printf
*/

#ifndef MY_PRINTF_H_
# define MY_PRINTF_H_

# include <stdarg.h>

# define MSC(s, c) my_str_contains(s, c)

typedef struct s_prtf {
    char *oflags;
    int rflag;
    int width;
    int has_precision;
    int precision;
    int ret_val;
} prtf_t;

typedef int (*my_printf_func_arr)(va_list ap, prtf_t *ft);

int my_printf(char *format, ...);

int parser(prtf_t *ft, int i, char *str, va_list ap);
int print_char(va_list ap, prtf_t *ft);
int print_str(va_list ap, prtf_t *ft);
int print_str_octal(va_list ap, prtf_t *ft);
int print_lower_hex(va_list ap, prtf_t *ft);
int print_upper_hex(va_list ap, prtf_t *ft);
int print_nbr(va_list ap, prtf_t *ft);
int print_long_base(va_list ap, prtf_t *ft);
int print_binary(va_list ap, prtf_t *ft);
int print_unbr_octal(va_list ap, prtf_t *ft);
int print_unbr_decimal(va_list ap, prtf_t *ft);
int print_percent(va_list ap, prtf_t *ft);
int is_opt_flag(char c);
int is_req_flag(char c);
int get_opt_flags(int i, char *str, prtf_t *ft);
int get_req_flags(int i, char *str, prtf_t *ft);
int my_str_contains(char *str, char c);
int my_printf_handle_numbers_p(char **str, prtf_t *ft);

#endif /* !MY_PRINTF_H_ */