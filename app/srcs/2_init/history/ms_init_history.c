/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:14 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 19:57:59 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_init_history(t_ms *ms)
{
	int		fd;
	char	*line;
	char	*path;

	ms->history_i = 1;
	path = ft_printf_to_var("/home/%s/.bash_history", \
		ms_find_env_value(ms, "USER"));
	fd = open(path, O_RDONLY);
	ms->history = malloc(sizeof(struct s_history));
	ms->history->next = NULL;
	ms->history->prev = NULL;
	line = get_next_line(fd);
	ms->history->line = line;
	ms->history->index = ms->history_i;
	ms->history->l_c_exit_code = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			ms_add_history(ms, line, NULL);
	}
	ft_free_ptr((void *) &path);
	get_next_line(-1);
}
