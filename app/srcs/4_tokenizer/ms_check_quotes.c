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

void	ms_check_quotes_2(char *line, int i, int j)
{
	int		quote_terminated;

	quote_terminated = 0;
	while (line[j])
	{
		if (line[j] == '"')
		{
			quote_terminated = 1;
			break ;
		}
		j++;
	}
	j = i;
	while (line[j])
	{
		if (quote_terminated && line[j] == '"')
		{
			line[j] = ' ';
			j++;
		}
		if (line[j] == ' ')
		{
			line[j] = '-';
		}
		j++;
	}
}

void	ms_check_quotes(t_ms *ms)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = ms->shell_line;
	if (ft_strchr(line, '\'') == NULL)
	{
		while (line[i])
		{
			if (line[i] == '"')
			{
				j = i + 1;
				ms_check_quotes_2(line, j, i);
				break ;
			}
			i++;
		}
	}
}
