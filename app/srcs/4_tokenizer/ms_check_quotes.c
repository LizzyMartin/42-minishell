/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 21:48:42 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_remove_char(char *s, char c)
{
	int new;
	int old;

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

static int count_char(char *s, char c)
{
	int i;
	int count;

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

void	ms_check_quotes(t_ms *ms)
{
	char	*line;
	char 	*goal;
	char 	**shell_line_splitted;
	int		i;
	int 	space;
	int 	space_index;

	i = 0;
	space = 0;
	space_index = -1;
	goal = ft_strdup("");
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
	line = goal + space_index + 1;
	shell_line_splitted = ft_split(ms->shell_line, ' ');
	if (ft_strchr(line, '"') && count_char(line, '"') % 2 == 0)
		ms_remove_char(line, '"');
	ms->shell_line_tokenized = ft_printf_to_var("%s %s", shell_line_splitted[0], line);
	ms->shell_line_tokenized[space_index] = ' ';
}
