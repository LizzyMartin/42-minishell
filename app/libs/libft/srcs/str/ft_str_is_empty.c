#include <libft.h>

int ft_str_is_empty(char *str)
{
    if (*str == '\0' || str == NULL)
        return (1);
    return (0);
}