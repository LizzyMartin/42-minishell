#include <libft.h>

void    ft_fd_print(int fd)
{
    char *tmp;

    tmp = get_next_line(fd);
    while (tmp)
    {
        ft_printf("%s", tmp);
        free(tmp);
        tmp = get_next_line(fd);
    }
    free(tmp);
    get_next_line(-1);
}