/*
** EPITECH PROJECT, 2018
** task02
** File description:
** my include file
*/

#ifndef MY_H_
# define MY_H_

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include "my_printf.h"
# include "get_next_line.h"

int my_str_istabspace(char *str);
int my_putchar(char c);
int my_isneg(int n);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char *str);
int my_strlen(char *str);
int my_getnbr(char *str);
void my_sort_int_array(int *array, int size);
int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char *src);
char *my_strncpy(char *dest, char *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *string, char *substring);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char *str);
int my_str_isnum(char *str);
int my_str_islower(char *str);
int my_str_isupper(char *str);
int my_str_isprintable(char *str);
int my_showstr(char *str);
int my_showmem(char *str, int size);
char *my_strcat(char *dest, char *src);
char *my_strncat(char *dest, char *src, int n);
char **my_str_to_word_array(char *str);
int my_show_word_array(char * *tab);
int my_putnbr_base(int nbr, char *base, int pos);
char *my_strdup(char *str);
void *my_memset(void *ptr, int c, size_t n);
void *x_memset(int c, size_t nmemb, size_t size);
char *my_realloc(char *ptr, size_t size);
long int my_strtol(char *str, char **endptr);
char *my_ltoa_base(long int nbr, char *str, char *base, int i);
void my_puterr(char *str, int err_code);
int my_showstr_octal(char *str);
int my_putlong_base(long nbr, char *base, int pos);
int my_putunbr_base(unsigned int nbr, char *base, int pos);
int my_stricmp(char const *s1, char const *s2);
int my_strnicmp(char const *s1, char const *s2, int n);
char **my_str_to_wordtab(char *str, char **delims);
char *get_next_line(int fd);
int my_str_is_alphanum(char *str);
int my_tab_size(char **tab);
int my_tab_contains_char(char **tab, char c);
int my_tab_contains_str(char **tab, char *str);
char *my_mstrcat(char *str1, char *str2);
char **wordtab_quotes(char *str, char **delims);
char **wordtab(char *str, char **delims);

int my_strstr_intermediate(char *a, char *b);
int check_sign(char *str);
void calculate_new_number(int *nb, int to_add, int positive);
int is_alphanum(char c);
char *epur_str(char *str);
int count_words(char *str);
void point_words(char **arr, char *str);
void end_ltoa_base(char *str, int neg);
char *stricmp_tolower(char const *str);
int strtwt_free_tab(char **tab);
int strtwt_is_delim(char *str, char **delims);
char *strtwt_epur_str(char *str, char **delims, int free_str);
int wq_free_tab(char **tab);
int wq_is_delim(char *str, char **delims, int mode);
int wq_keep_quotes(char *str, char *res, int *i, int mode);
char *wq_epur_str(char *str, char **delims, int free_str);
int wt_free_tab(char **tab);
int wt_utils(char *str, char **delims, int mode, int pos);
int wt_count_elems(char *str, char **delims);
char *wt_epur_str(char *str, char **delims, int free_str);
char *my_itoa(int nb);
char *my_strnncat(int start, int end, char *str, char *add_str);

#endif /* !MY_H_ */
