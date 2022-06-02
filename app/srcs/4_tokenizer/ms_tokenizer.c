/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:43:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/01 23:28:28 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ms_get_home_value(t_ms *ms)
{
	if (ms_is_in_env(ms, "HOME"))
		return (ms_find_env_value(ms, "HOME"));
	else if (ms_is_in_env(ms, "USER"))
		return (ft_printf_to_var("/home/%s", ms_find_env_value(ms, "USER")));
	else
		return (ft_strdup("/home"));
}

void ms_expand_dolar(t_ms *ms)
{
	char *line;
	char *no_dolar;
	char *value;
	char *dolar_cmd;
	int	i;

	i = 0;
	line = ms->shell_line_tokenized;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (ms->has_double_quotes && ft_strchr(line, ' '))
			{
				dolar_cmd = ft_substr(line + i, 0, ft_str_indexof(line + i, T_SPACE, ft_strlen(line + i) - 1) - 1);
			}
			else
			{
				dolar_cmd = ft_substr(line + i, 0, ft_strlen(line) - 1);
			}
			if (ms->has_single_quotes == 0)
			{
				no_dolar = ft_substr(dolar_cmd, 1, ft_strlen(dolar_cmd));
				if (ms_is_in_env(ms, no_dolar))
				{
					value = ms_find_env_value(ms, no_dolar);
					ms->shell_line_tokenized = ft_str_replace_all(line, dolar_cmd, value);
				}
			}
		}
		i++;
	}
}

int	ms_tokenizer(t_ms *ms)
{
	char	*tmp;
	char	*tmp2;
	char	*chr_tmp;

	if (ms_sintax(ms) == 1)
		return (1);
	ms_check_quotes(ms);
	ms_expand_dolar(ms);
	ft_printf("\n%s\n", ms->shell_line_tokenized);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, "&&", T_CONNECTOR_AND);
	ms->shell_line_tokenized = ft_strdup(tmp);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, " | ", T_PIPE);
	ms->shell_line_tokenized = ft_strdup(tmp);
	ft_free_ptr((void *) &tmp);
	chr_tmp = ft_chr_to_str('~', 1);
	tmp2 = ms_get_home_value(ms);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, chr_tmp, tmp2);
	ft_free_ptr((void *) &chr_tmp);
	ms->shell_line_tokenized = ft_strdup(tmp);
	ms_wildcard(ms);
	return (0);
}
