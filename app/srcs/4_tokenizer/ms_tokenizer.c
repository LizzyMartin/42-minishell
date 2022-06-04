/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:43:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 20:40:06 by acapela-         ###   ########.fr       */
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
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, "||", T_CONNECTOR);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, "&&", T_CONNECTOR);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, "|", T_PIPE);
}

int ms_tokenizer(t_ms *ms)
{
	ms->shell_line_tokenized = ft_strdup(ms->shell_line);
	ms->is_aux_env = 0;
	int equal_index = ft_str_indexof(ms->shell_line_tokenized, "=", ft_strlen(ms->shell_line_tokenized));
	int space_index = ft_str_indexof(ms->shell_line_tokenized, " ", ft_strlen(ms->shell_line_tokenized));
	if (equal_index != -1 && ms->shell_line_tokenized[equal_index - 1] != ' ')
		ms->is_aux_env = 1;
	if (space_index != -1 && space_index < equal_index)
		ms->is_aux_env = 0;
	if (ms_sintax(ms) == 1)
		return (1);
	ms_check_quotes(ms);
	ms_expand_dolar(ms);
	// lidando com casos gato==miau
	if (ms->is_aux_env)
	{
		char *key = ft_substr(ms->shell_line_tokenized, 0, equal_index + 1);
		char *value = ft_substr(ms->shell_line_tokenized, equal_index + 2, ft_strlen(ms->shell_line_tokenized));
		ms_add_env(&ms->aux_envs, key, value);
		return (1);
	}
	ms_basic_replaces(ms);
	ms_home_value(ms);
	ms_wildcard(ms);
	return (0);
}
