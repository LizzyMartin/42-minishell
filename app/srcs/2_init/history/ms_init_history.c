/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:14 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 22:10:48 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_init_history(t_ms *ms)
{
	int		fd;
	char	*line;
	char	*path;
	char	*tmp;
	char	*trim;

	tmp = ms_find_env_value(ms, "USER");
	ms->history_i = 1;
	path = ft_printf_to_var("/home/%s/.bash_history", tmp);
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	trim = ft_strtrim(line, "\n");
	while (line)
	{
		add_history(trim);
		ms_add_history(ms, line, NULL);
		line = get_next_line(fd);
		trim = ft_strtrim(line, "\n");
	}
	get_next_line(-1);
	ft_free_ptr((void *) &path);
	close(fd);
}
