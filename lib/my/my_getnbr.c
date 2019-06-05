/*
** EPITECH PROJECT, 2018
** my_getnbr
** File description:
** my_getnbr
*/

int check_sign(char *str)
{
    int i = 0;
    int minus_counter = 0;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            ++minus_counter;
        ++i;
    }
    if (minus_counter % 2 == 0)
        return (1);
    else
        return (0);
}

int calculate_new_number(int *nb, int to_add, int positive)
{
    if (positive && (*nb * 10 + to_add >= 0)) {
        *nb = *nb * 10 + to_add;
        return (0);
    } else if (!positive && (*nb * 10 - to_add <= 0)) {
        *nb = *nb * 10 - to_add;
        return (0);
    } else {
        return (1);
    }
    return (0);
}

int my_getnbr(char *str)
{
    int positive = check_sign(str);
    int nb = 0;
    int nb_fnd = 0;
    int i = 0;
    int error = 0;

    while (str[i]=='-' || str[i]=='+' || (str[i]>='0' && str[i]<='9')) {
        if (str[i] >= '0' && str[i] <= '9') {
            error = calculate_new_number(&nb, str[i] - 48, positive);
            nb_fnd = 1;
        }
        else if (nb_fnd)
            return (nb);
        if (error)
            return (0);
        ++i;
    }
    return (nb);
}