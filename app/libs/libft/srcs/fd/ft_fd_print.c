#include <libft.h>

void    ft_fd_print(int fd)
{
    char *tmp;

    tmp = get_next_line(fd);
    while (tmp)
    {
        ft_printf("%s", tmp);
        tmp = get_next_line(fd);
    }
}
