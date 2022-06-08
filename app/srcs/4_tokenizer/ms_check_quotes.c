/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/07 22:05:00 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	treat_having_quotes(t_ms *ms, char *tmp, int *i)
{
	int		first;
	int		second;
	char	*line_inside_quotes;
	int		final;
	int		size;

	size = 0;
	first = *i;
	second = ft_str_indexof(ms->shell_line + first + 1, \
	ft_chr_to_str(ms->shell_line[*i], 1), size - *i);
	line_inside_quotes = ft_substr(ms->shell_line, first + 1, second);
	tmp = ft_printf_to_var("%s %c%s%c", ft_substr(ms->shell_line, \
	0, *i), ms->shell_line[*i], ft_str_replace_all(line_inside_quotes, \
	" ", T_SPACE), ms->shell_line[*i]);
	*i += second + 1;
	ms->shell_line_tokenized = tmp;
	final = ft_str_indexof(ms->shell_line + *i + 1, \
	ft_chr_to_str(ms->shell_line[*i], 1), size);
	tmp = ft_printf_to_var("%s %s", \
	ms->shell_line_tokenized, ft_substr(ms->shell_line, *i + 1, final));
	ms->shell_line_tokenized = tmp;
}

void	ms_check_quotes(t_ms *ms)
{
	int		i;
	char	*tmp;
	int		size;
	char	**cmd;

	if (ft_strchr(ms->shell_line_tokenized, '\'') || \
		ft_strchr(ms->shell_line_tokenized, '"'))
	{
		size = (int) ft_strlen(ms->shell_line) - 1;
		if (ms->is_aux_env)
			i = 0;
		else
		{
			cmd = ft_split(ms->shell_line, ' ');
			tmp = cmd[0];
			ms->shell_line_tokenized = tmp;
			i = ft_str_indexof(ms->shell_line, ft_chr_to_str(' ', 1), size);
		}
		while (ms->shell_line[i])
		{
			if (ms->shell_line[i] == '"' || ms->shell_line[i] == '\'')
				treat_having_quotes(ms, tmp, &i);
			i++;
		}
	}
}
