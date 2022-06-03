/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:43:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/02 23:42:02 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *ms_get_home_value(t_ms *ms)
{
	if (ms_is_in_env(ms, "HOME"))
		return (ms_find_env_value(ms, "HOME"));
	else if (ms_is_in_env(ms, "USER"))
		return (ft_printf_to_var("/home/%s", ms_find_env_value(ms, "USER")));
	else
		return (ft_strdup("/home"));
}

void ms_has_single_quotes(t_ms *ms, char *dolar_cmd, char *line)
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
	ms->shell_line_tokenized = "";
	while (line_splited[i])
	{
		int index_double = ft_str_indexof(line_splited[i], "\"", ft_strlen(line_splited[i]) - 1);
		int index_single = ft_str_indexof(line_splited[i], "'", ft_strlen(line_splited[i]) - 1);
		if (index_double != -1 && index_single != -1 && index_double < index_single)
			ms->has_double_quotes = 1;
		else if (index_double != -1 && index_single != -1 && index_single < index_double)
			ms->has_single_quotes = 1;
		else if (index_double != -1 && index_single == -1)
			ms->has_double_quotes = 1;
		else if (index_single != -1 && index_double == -1)
			ms->has_single_quotes = 1;
		j = 0;
		if (ft_strchr(line_splited[i], '$') == NULL || ms->has_single_quotes)
		{
			ms->shell_line_tokenized = ft_printf_to_var("%s %s", ms->shell_line_tokenized, line_splited[i]);
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
					ms_has_single_quotes(ms, dolar_cmd, line_splited[i]);
				}
				j++;
			}
		}
		i++;
	if (ms->has_double_quotes)
		ms_remove_char(ms->shell_line_tokenized, '"');
	else if (ms->has_single_quotes)
		ms_remove_char(ms->shell_line_tokenized, '\'');
	}
}

int ms_tokenizer(t_ms *ms)
{
	char *tmp;
	char *tmp2;
	char *chr_tmp;

	if (ms_sintax(ms) == 1)
		return (1);

	// replace espaço dentro do aspa por token T_SPACE
	int size = ft_strlen(ms->shell_line) - 1;
	char **cmdd = ft_split(ms->shell_line, ' ');
	ms->shell_line_tokenized = cmdd[0];
	int i = ft_str_indexof(ms->shell_line, ft_chr_to_str(' ', 1), size);
	while (ms->shell_line[i])
	{
		if (ms->shell_line[i] == '"' || ms->shell_line[i] == '\'')
		{
			char *delimiter = ft_chr_to_str(ms->shell_line[i], 1);
			int first = i;
			int second = ft_str_indexof(ms->shell_line + first + 1, ft_chr_to_str(ms->shell_line[i], 1), size - i);

			char *line_inside_quotes = ft_substr(ms->shell_line, first + 1, second);
			ms->shell_line_tokenized = ft_printf_to_var("%s %c%s%c", ms->shell_line_tokenized, ms->shell_line[i], ft_str_replace_all(line_inside_quotes, " ", T_SPACE), ms->shell_line[i]);
			i += second + 1;

			int final = ft_str_indexof(ms->shell_line + i + 1, delimiter, size);
			char *semnome = ft_substr(ms->shell_line, i + 1, final);
			ms->shell_line_tokenized = ft_printf_to_var("%s %s", ms->shell_line_tokenized, semnome);
		}
		i++;
	}
	//
	ms_expand_dolar(ms);
	ft_printf("#%s#\n", ms->shell_line_tokenized);
	// tokenization
	tmp = ft_str_replace_all(ms->shell_line_tokenized, "&&", T_CONNECTOR_AND);
	ms->shell_line_tokenized = ft_strdup(tmp);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, " | ", T_PIPE);
	ms->shell_line_tokenized = ft_strdup(tmp);
	ft_free_ptr((void *)&tmp);
	chr_tmp = ft_chr_to_str('~', 1);
	tmp2 = ms_get_home_value(ms);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, chr_tmp, tmp2);
	ft_free_ptr((void *)&chr_tmp);
	ms->shell_line_tokenized = ft_strdup(tmp);
	ms_wildcard(ms);
	return (0);
}
