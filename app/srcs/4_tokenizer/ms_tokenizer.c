/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:43:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/08 02:01:45 by argel            ###   ########.fr       */
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

static void	ms_home_value(t_ms *ms)
{
	char	*chr_tmp;
	char	*tmp;
	char	*tmp2;

	chr_tmp = ft_chr_to_str('~', 1);
	tmp2 = ms_get_home_value(ms);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, chr_tmp, tmp2);
	ms->shell_line_tokenized = ft_strdup(tmp);
	ft_free_ptr((void *) &chr_tmp);
}

static void	ms_basic_replaces(t_ms *ms)
{
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, \
	"||", T_CONNECTOR);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, \
	"&&", T_CONNECTOR);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized, \
	"|", T_PIPE);
}

static void	ms_aux_env(t_ms *ms, int equal_index)
{
	char	*key;
	char	*value;

	if (ms->is_aux_env)
	{
		key = ft_substr(ms->shell_line_tokenized, 0, \
		equal_index + 1);
		value = ft_substr(ms->shell_line_tokenized, \
		equal_index + 2, ft_strlen(ms->shell_line_tokenized));
		ms_add_env(&ms->aux_envs, key, value);
	}
}

int	ms_tokenizer(t_ms *ms)
{
	int	equal_index;
	int	space_index;

	ms->shell_line_tokenized = ms->shell_line;
	ms->is_aux_env = 0;
	equal_index = ft_str_indexof(ms->shell_line_tokenized, \
	"=", ft_strlen(ms->shell_line_tokenized));
	space_index = ft_str_indexof(ms->shell_line_tokenized, \
	" ", ft_strlen(ms->shell_line_tokenized));
	if (equal_index != -1 && ms->shell_line_tokenized[equal_index - 1] != ' ')
		ms->is_aux_env = 1;
	if (space_index != -1 && space_index < equal_index)
		ms->is_aux_env = 0;
	if (ms_sintax(ms) == 1)
		return (1);
	if (ft_count_chr(ms->shell_line_tokenized, '"') != 1 \
	|| ft_count_chr(ms->shell_line_tokenized, '\'') != 1)
		ms_check_quotes(ms);
	ms_expand_dolar(ms);
	ms_aux_env(ms, equal_index);
	ms_basic_replaces(ms);
	ms_home_value(ms);
	ms_wildcard(ms);
	return (0);
}
