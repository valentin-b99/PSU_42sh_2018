/*
** EPITECH PROJECT, 2019
** inhibitors
** File description:
** inhibitors
*/

#include "../../../include/my.h"
#include "../../../include/mysh.h"

int remove_inhibitors(char *str)
{
    str[my_strlen(str) - 1] = str[my_strlen(str) - 1] == ' ' ? 0 : ' ';
    return (0);
}

int count_inhibitors(char *str)
{
    int count = 0;

    for (int i = my_strlen(str) - 1; i >= 0 && str[i] == '\\'; --i)
        count += 1;
    return (count);
}

int inhibitors_loop(shell_t *ft, char *s)
{
    int quit = 0;

    remove_inhibitors(ft->input);
    free(s);
    write(0, "? ", 2);
    while (!quit && (s = get_next_line(0))) {
        s = strtwt_epur_str(s, (char*[]){ " ", "\t", NULL }, 1);
        if (!s || !my_strlen(s) || !(count_inhibitors(s) % 2))
            quit = 1;
        !quit ? write(0, "? ", 2) : 0;
        s ? ft->input = my_realloc(ft->input, my_strlen(ft->input) +
            my_strlen(s) + 1) : 0;
        s ? my_strcat(ft->input, s) : 0;
        s && !quit ? remove_inhibitors(ft->input) : 0;
        free(s);
        s = NULL;
    }
    return (0);
}

int inhibitors(shell_t *ft, char *s)
{
    s = strtwt_epur_str(s, (char*[]){ " ", "\t", NULL }, 1);

    ft->input = s && my_strlen(s) ? my_strdup(s) : x_memset(0, 1, sizeof(char));
    if (s && my_strlen(s) > 0 && (count_inhibitors(s) % 2))
        inhibitors_loop(ft, s);
    else {
        inhibitors_inside(ft);
        return (rint_free(s) | 0);
    }
    inhibitors_inside(ft);
    return (0);
}
