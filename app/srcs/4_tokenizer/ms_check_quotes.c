/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 18:09:34 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_check_quotes(t_ms *ms)
{
	if (ft_strchr(ms->shell_line_tokenized, '\'') ||
		ft_strchr(ms->shell_line_tokenized, '"'))
	{
		int size = ft_strlen(ms->shell_line) - 1;
		char **cmd = ft_split(ms->shell_line, ' ');
		ms->shell_line_tokenized = cmd[0];
		int i = ft_str_indexof(ms->shell_line, ft_chr_to_str(' ', 1), size);
		while (ms->shell_line[i])
		{
			if (ms->shell_line[i] == '"' || ms->shell_line[i] == '\'')
			{
				char *delimiter = ft_chr_to_str(ms->shell_line[i], 1);
				int first = i;
				int second = ft_str_indexof(ms->shell_line + first + 1, ft_chr_to_str(ms->shell_line[i], 1), size - i);

				char *line_inside_quotes = ft_substr(ms->shell_line, first + 1, second);
				ms->shell_line_tokenized = ft_printf_to_var("%s %c%s%c", ft_substr(ms->shell_line, 0, i), ms->shell_line[i], ft_str_replace_all(line_inside_quotes, " ", T_SPACE), ms->shell_line[i]);
				i += second + 1;

				int final = ft_str_indexof(ms->shell_line + i + 1, delimiter, size);
				char *semnome = ft_substr(ms->shell_line, i + 1, final);
				ms->shell_line_tokenized = ft_printf_to_var("%s %s", ms->shell_line_tokenized, semnome);
			}
			i++;
		}
	}
}
