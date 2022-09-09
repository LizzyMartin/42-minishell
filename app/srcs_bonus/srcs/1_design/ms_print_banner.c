/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_banner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:23 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	print_banner(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("srcs/1_design/banner.txt", O_RDONLY);
	while (i < 33)
	{
		line = get_next_line(fd);
		if (line != NULL)
			ft_printf("%s%s%s", BOLD_YELLOW, line, END_COLOR);
		ft_free_ptr((void *) &line);
		i++;
	}
	close(fd);
}
