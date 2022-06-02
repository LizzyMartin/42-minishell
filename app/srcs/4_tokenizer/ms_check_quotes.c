/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/02 16:07:29 by argel            ###   ########.fr       */
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

static void	threat_quotes(t_ms *ms, char *beggin, char *goal, int space_index)
{
	char	*line;
	char	*line_inside_quotes;
	int		first_i_d;
	int		first_i_s;
	int		last_i;

	line = goal + space_index + 1;
	first_i_d = ft_str_indexof(line, ft_chr_to_str('"', \
	1), ft_strlen(line) - 1);
	first_i_s = ft_str_indexof(line, ft_chr_to_str('\'', \
	1), ft_strlen(line) - 1);
	last_i = ft_str_indexof(line + first_i_d + 1, \
	ft_chr_to_str('"', 1), ft_strlen(line) - 1);
	line_inside_quotes = ft_substr(line, first_i_d + 1, \
	last_i);
	if (first_i_s > first_i_d && ft_strchr(line, '"') \
	&& count_char(line, '"') % 2 == 0)
	{
		if (!ft_strchr(line, ' '))
		{
			ms_remove_char(ms->shell_line_tokenized, '"');
			return ;
		}
		ms->has_double_quotes = 1;
		ms->shell_line_tokenized = ft_printf_to_var("%s %s%s%s", \
		beggin, ft_substr(line, 0, first_i_d), \
		ft_str_replace_all(line_inside_quotes, " ", T_SPACE), \
		ft_substr(line, last_i + first_i_d + 2, ft_strlen(line) - 1));
	}
	else if (ft_strchr(line, '\'') && count_char(line, '\'') % 2 == 0)
	{
		ms->has_single_quotes = 1;
		return ;
	}
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
	ms->shell_line_tokenized = ft_strdup(ms->shell_line);
	if (space_index != -1)
	{
		threat_quotes(ms, ft_split(ms->shell_line, ' ')[0], goal, space_index);
		return ;
	}
	ft_free_ptr((void **) &goal);
}
