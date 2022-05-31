/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 15:13:31 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ms_get_home_value(t_ms *ms)
{
	if (ms_is_in_env(ms, "HOME"))
		return (ms_find_env_value(ms, "HOME"));
	else if (ms_is_in_env(ms, "USER"))
		return (ft_printf_to_var("/home/%s", ms_find_env_value(ms, "USER")));
	else
		return (ft_strdup("/home"));
}

void	ms_tokenizer(t_ms *ms)
{
	char	*tmp;
	char    *tmp2;
	char    *chr_tmp;
	
	ms_check_quotes(ms);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, " && ", T_CONNECTOR);
	ms->shell_line_tokenized = ft_strdup(tmp);
	// ft_free_ptr((void *) &tmp);
	
	tmp = ft_str_replace_all(ms->shell_line_tokenized, " | ", T_PIPE);
	ms->shell_line_tokenized = ft_strdup(tmp);	
	ft_free_ptr((void *) &tmp);
	
	chr_tmp = ft_chr_to_str('~', 1);
	tmp2 = ms_get_home_value(ms);
	tmp = ft_str_replace_all(ms->shell_line_tokenized, chr_tmp, tmp2);
	ft_free_ptr((void *) &chr_tmp);
	//if (tmp2 != NULL)
		//ft_free_ptr((void *) &tmp2);
	ms->shell_line_tokenized = tmp;
	ms_wildcard(ms);
}
