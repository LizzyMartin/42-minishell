/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_dolar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:55:01 by argel             #+#    #+#             */
/*   Updated: 2022/06/06 20:05:29 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void ms_has_single_quotes(t_ms *ms, char *dolar_cmd, char *line)
{
	char *no_dolar;
	char *value;

	no_dolar = ft_substr(dolar_cmd, 1, ft_strlen(dolar_cmd));
	if (ms_is_in_env(ms, no_dolar))
	{
		value = ms_find_env_value(ms, no_dolar);
		ms->shell_line_tokenized = ft_printf_to_var("%s %s", ms->shell_line_tokenized, ft_str_replace_all(line, dolar_cmd, value));
	}
}

void ms_expand_dolar(t_ms *ms)
{
	char **line_splited;
	char *dolar_cmd;
	int i;
	int j;

	i = 0;
	line_splited = ft_split(ms->shell_line_tokenized, ' ');
	if (line_splited[1] && ft_strncmp(line_splited[1], "$?", 2) == 0)
	    return ;
	
	ms->shell_line_tokenized = "";
	while (line_splited[i])
	{
		ms->has_double_quotes = 0;
		ms->has_single_quotes = 0;
		int index_double = ft_str_indexof(line_splited[i], "\"", ft_strlen(line_splited[i]) - 1);
		int index_single = ft_str_indexof(line_splited[i], "'", ft_strlen(line_splited[i]) - 1);
		
		if (index_double != -1 && index_single != -1 && index_double < index_single)
			ms->has_double_quotes = 1;
		else if (index_double != -1 && index_single != -1 && index_single < index_double)
			ms->has_single_quotes = 1;
		
		if (index_double != -1 && index_single == -1)
			ms->has_double_quotes = 1;
		else if (index_single != -1 && index_double == -1)
			ms->has_single_quotes = 1;

		if (ft_count_chr(line_splited[i], '\'') == 1)
			ms->has_single_quotes = 0;
		if (ft_count_chr(line_splited[i], '"') == 1)
			ms->has_double_quotes = 0;
			
		j = 0;
		if (ft_strchr(line_splited[i], '$') == NULL || ms->has_single_quotes)
		{
			char *tmp = ft_strjoin(ft_strdup(ms->shell_line_tokenized), " ");
			ms->shell_line_tokenized = ft_strjoin(tmp, ft_strdup(line_splited[i]));
		}
		else
		{
			while (line_splited[i][j])
			{
				if (line_splited[i][j] == '$')
				{
					int final = 0;
					while (line_splited[i][j + final] != '\'' &&
						   line_splited[i][j + final] != '\"' &&
						   line_splited[i][j + final] != '\0' &&
						   line_splited[i][j + final] != ' ')
						final++;
					dolar_cmd = ft_substr((line_splited[i] + j), 0, final);
					ms_has_single_quotes(ms, dolar_cmd, ft_strdup(line_splited[i]));
				}
				j++;
			}
		}
		i++;
	if (ms->has_double_quotes)
		ft_remove_char(ms->shell_line_tokenized, '"');
	if (ms->has_single_quotes)
		ft_remove_char(ms->shell_line_tokenized, '\'');
	}
	ft_mtx_free((void **) line_splited);
}
