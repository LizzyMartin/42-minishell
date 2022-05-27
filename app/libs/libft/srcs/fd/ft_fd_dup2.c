#include <libft.h>

void    ft_fd_dup2(int read_from, int write_in)
{
	char	tmp[2];

    while (read(read_from, tmp, 2) != 0)
		write(write_in, tmp, 2);
}
