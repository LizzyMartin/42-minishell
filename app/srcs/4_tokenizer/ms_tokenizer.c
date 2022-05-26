/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 21:36:19 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ms_get_home_value(t_ms *ms)
{
	if (is_in_env(ms, "HOME"))
		return (find_env_value(ms, "HOME"));
	else if (is_in_env(ms, "USER"))
		return (ft_printf_to_var("/home/%s", find_env_value(ms, "USER")));
	else
		return (ft_strdup("/home"));
}

void	ms_tokenizer(t_ms *ms)
{
	ms_check_quotes(ms);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line, " && ",
			T_CONNECTOR);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized,
			" | ", T_PIPE);
	ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized,
			ft_chr_to_str('~', 1), ms_get_home_value(ms));
	ms_wildcard(ms);
}
