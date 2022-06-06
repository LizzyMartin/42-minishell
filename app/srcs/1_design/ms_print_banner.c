/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_banner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:23 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 13:29:47 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_banner(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("srcs/1_design/banner.txt", O_RDONLY);
	while (i < 25)
	{
		line = get_next_line(fd);
		if (line != NULL)
			ft_printf("%s%s", BOLD_YELLOW, line);
		free(line);
		i++;
	}
	ft_printf(WHITE);
	close(fd);
}
