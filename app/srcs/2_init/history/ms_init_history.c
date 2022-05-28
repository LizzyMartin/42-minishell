/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:14 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/28 00:53:32 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_init_history(t_ms *ms)
{
	int		fd;
	char	*line;
	char	*path;
	char	*tmp;

	tmp = ms_find_env_value(ms, "USER");
	ms->history_i = 1;
	path = ft_printf_to_var("/home/%s/.bash_history", tmp);
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
		if (line)
		{
			add_history(ft_strtrim(line, "\n"));
			ms_add_history(ms, line, NULL);
		}
		line = get_next_line(fd);
	}
	ft_free_ptr((void *) &path);
//	ft_free_ptr((void *) &tmp);
	get_next_line(-1);
}
