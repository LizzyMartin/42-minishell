#include <libft.h>

void    ft_fd_print(int fd)
{
    char	tmp[2];

    while (read(fd, tmp, 2) != 0)
		write(1, tmp, 2);
}
