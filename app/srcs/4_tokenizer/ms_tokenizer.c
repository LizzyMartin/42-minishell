/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:43:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 18:19:15 by acapela-         ###   ########.fr       */
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
	char	*dupped;
	char	*tmp;
	char	*tmp2;

	chr_tmp = ft_chr_to_str('~', 1);
	tmp2 = ft_strdup(ms_get_home_value(ms));
	dupped = ft_strdup(ms->shell_line_tokenized);
	tmp = ft_str_replace_all(dupped \
			, chr_tmp, tmp2);
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ft_free_ptr((void *) &chr_tmp);
	ft_free_ptr((void *) &tmp2);
	ms->shell_line_tokenized = tmp;
	ft_free_ptr((void *) &chr_tmp);
}

static void	ms_aux_env(t_ms *ms, int equal_index)
{
	char	*key;
	char	*value;

	key = ft_substr(ms->shell_line_tokenized, 0, \
	equal_index + 1);
	value = ft_substr(ms->shell_line_tokenized, \
	equal_index + 2, ft_strlen(ms->shell_line_tokenized));
	ms_add_env(&ms->aux_envs, key, value);
	ft_free_ptr((void *) &key);
	ft_free_ptr((void *) &value);
}

static void	ms_is_aux_env(t_ms *ms, int *equal_index)
{
	int	space_index;

	ms->shell_line_tokenized = ft_strdup(ms->shell_line);
	ms->is_aux_env = 0;
	*equal_index = ft_str_indexof(ms->shell_line_tokenized, \
	"=", ft_strlen(ms->shell_line_tokenized));
	space_index = ft_str_indexof(ms->shell_line_tokenized, \
	" ", ft_strlen(ms->shell_line_tokenized));
	if (*equal_index != -1 && ms->shell_line_tokenized[*equal_index - 1] != ' ')
		ms->is_aux_env = 1;
	if (space_index != -1 && space_index < *equal_index)
		ms->is_aux_env = 0;
}

int	ms_tokenizer(t_ms *ms)
{
	int	equal_index;

	ms_is_aux_env(ms, &equal_index);
	if (ms_sintax(ms) == 1)
		return (1);
	if (ms_count_char(ms->shell_line_tokenized, '"') != 1 \
	&& ms_count_char(ms->shell_line_tokenized, '\'') != 1)
		ms_check_quotes(ms);
	else
	{
		ft_putstr_fd("miniheaven: close your quotes\n", 1);
		return (1);
	}
	ms_quotes_vs_connectors(ms, ms->shell_line_tokenized);
	if (ft_strnstr(ms->shell_line_tokenized, "$?", 2) == NULL)
		ms_expand_dolar(ms);
	if (ms->is_aux_env)
	{
		ms_aux_env(ms, equal_index);
		return (1);
	}
	ms_home_value(ms);
	if (ft_strrchr(ms->shell_line_tokenized, '*') != NULL)
		ms_wildcard(ms);
	return (0);
}
