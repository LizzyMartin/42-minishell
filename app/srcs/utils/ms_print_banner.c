#include <minishell.h>

void	print_banner(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("srcs/utils/banner.txt", O_RDONLY);
	while (i < 17)
	{
		line = get_next_line(fd);
		if (line != NULL)
			ft_printf("%s%s\n", BOLD_PURPLE, line);
		free(line);
		i++;
	}
	ft_printf(WHITE);
	free(line);
}
