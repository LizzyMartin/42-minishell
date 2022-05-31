/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:14 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 15:15:14 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_init_history(t_ms *ms)
{
	int		fd;
	char	*line;
	char	*path;
	char	*tmp;
	char 	*trim;
	//char	*tmp2;

	tmp = ms_find_env_value(ms, "USER");
	ms->history_i = 1;
	path = ft_printf_to_var("/home/%s/.bash_history", tmp);
	fd = open(path, O_RDONLY);
	
	// init history
	line = get_next_line(fd);
	trim = ft_strtrim(line, "\n");	
	
	ms->history = malloc(sizeof(struct s_history));
	ms->history->next = NULL;
	ms->history->prev = NULL;
	ms->history->line = line;
	ms->history->index = ms->history_i;
	ms->history->l_c_exit_code = 0;
	
	// iterate gnl
	while (line)
	{
		add_history(trim);		
		ms_add_history(ms, trim, NULL);	
		if (line != NULL)
			ft_free_ptr((void *) &line);
		if (trim != NULL)
			ft_free_ptr((void *) &trim);
		line = get_next_line(fd);
		trim = ft_strtrim(line, "\n");	
	}
	get_next_line(-1);
	ft_free_ptr((void *) &path);
	//ft_free_ptr((void *) &tmp);
	close(fd);
}
