/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 22:30:46 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_goal(const t_ms *ms, char *goal, int i, int space)
{
	int	space_index;

	while (ms->shell_line[i])
	{
		goal[i] = ms->shell_line[i];
		if (ms->shell_line[i] == ' ' && !space)
		{
			goal[i] = '-';
			space_index = i;
			space = 1;
		}
		i++;
	}
	return (space_index);
}

void	ms_remove_char(char *s, char c)
{
	int	new;
	int	old;

	new = 0;
	old = 0;
	while (s[old])
	{
		if (s[old] != c)
			s[new++] = s[old];
		old++;
	}
	s[new] = '\0';
}

static int	count_char(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	threat_quotes(t_ms *ms, char *goal, int space_index)
{
	char	*line;
	char	**shell_line_splitted;

	line = goal + space_index + 1;
	shell_line_splitted = ft_split(ms->shell_line, ' ');
	if (line[0] != '"' && line[1] != '\'')
	{
		if (line[0] != '\'' && ft_strchr(line, '"') \
			&& count_char(line, '"') % 2 == 0)
			ms_remove_char(line, '"');
	}
	ms->shell_line_tokenized = ft_printf_to_var("%s %s", \
		shell_line_splitted[0], line);
	ms->shell_line_tokenized[space_index] = ' ';
	ft_mtx_free((void **) shell_line_splitted);
}

void	ms_check_quotes(t_ms *ms)
{
	char	*goal;
	int		i;
	int		space;
	int		space_index;

	i = 0;
	space = 0;
	space_index = -1;
	goal = ft_calloc(ft_strlen(ms->shell_line), sizeof (char *));
	space_index = get_goal(ms, goal, i, space);
	if (space_index != -1)
	{
		threat_quotes(ms, goal, space_index);
		return ;
	}
	ft_free_ptr((void **) &goal);
	ms->shell_line_tokenized = ms->shell_line;
}
