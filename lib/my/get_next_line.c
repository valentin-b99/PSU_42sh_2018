/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** get_next_line
*/

#include "./my.h"

int gnl_reread(int *is, int fd, char *buff, char **str)
{
    int ret = 0;

    if (is[0] >= is[1]) {
        for (int i = 0; i < READ_SIZE; ++i)
            buff[i] = 0;
        is[0] = 0;
        if ((is[1] = read(fd, buff, READ_SIZE)) <= 0) {
            ret = str[0][0] == 0 ? -1 : ret;
            ret = str[0][0] != 0 ? 1 : ret;
        }
    } else {
        for (int i = 0; i < (is[0] + 1 >= is[1] ? READ_SIZE : 0); ++i)
            buff[i] = 0;
        is[0] = is[0] + 1 >= is[1] ? 0 : is[0] + 1;
        ret = 1;
    }
    return (ret);
}

char *get_next_line(int fd)
{
    static char buff[READ_SIZE];
    static int is[2] = { 0, 0 };
    int jr[2] = { 0, 0 };
    char *str = NULL;

    if (fd < 0 || READ_SIZE <= 0 || (buff[0] == 0 && (is[1] = read(fd, buff,
        READ_SIZE)) <= 0) || !(str = x_memset(0, 1, sizeof(char))))
        return (NULL);
    while (1) {
        if (is[0] < is[1] && buff[is[0]] != '\n' && buff[is[0]] != '\0') {
            str[jr[0]++] = buff[is[0]++];
            str = my_realloc(str, my_strlen(str) + 1);
        } else
            jr[1] = gnl_reread(is, fd, buff, &str);
        if (jr[1] == -1 || jr[1] == 1 || buff[0] == 0)
            return (jr[1] == -1 ? NULL : str);
    }
    return (str);
}
