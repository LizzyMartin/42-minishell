/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:43:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 22:59:14 by argel            ###   ########.fr       */
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

int	ms_tokenizer(t_ms *ms)
{
	char	*tmp;
	char	*tmp2;
	char	*chr_tmp;

	if (ms_sintax(ms) == 1)
		return (1);
	ms_check_quotes(ms);
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
