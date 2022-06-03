/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:43:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 01:14:01 by argel            ###   ########.fr       */
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

static void ms_home_value(t_ms *ms)
{
	char *chr_tmp;
    char *tmp;
	char *tmp2;

	chr_tmp = ft_chr_to_str('~', 1);
	tmp2 = ms_get_home_value(ms);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, chr_tmp, tmp2);
	ms->shell_line_tokenized = ft_strdup(tmp);
}

static void ms_basic_replaces(t_ms *ms)
{
	char *tmp;
	
	tmp = ft_str_replace_all(ms->shell_line_tokenized, "&&", T_CONNECTOR_AND);
	ms->shell_line_tokenized = ft_strdup(tmp);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, " | ", T_PIPE);
	ms->shell_line_tokenized = ft_strdup(tmp);
}

int ms_tokenizer(t_ms *ms)
{
	ms->shell_line_tokenized = ft_strdup(ms->shell_line);
	if (ms_sintax(ms) == 1)
		return (1);
	ms_check_quotes(ms);
	ms_expand_dolar(ms);
	ms_basic_replaces(ms);
	ms_home_value(ms);
	ms_wildcard(ms);
	return (0);
}
