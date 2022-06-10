/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/09 21:06:14 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_finish(t_ms *ms)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	clear_history();
	rl_clear_history();
	ms_free_history(ms);
	ms_free_env(ms);
	if (ms->shell_line)
	{
		ft_free_ptr((void *) &ms->shell_line);
		ms_free_prompt(ms, ms->p);
	}
	if (ms->shell_line_tokenized)
		ft_free_ptr((void *) &ms->shell_line_tokenized);
	if (ms->readline_var)
		ft_free_ptr((void *) &ms->readline_var);
	if (ms)
		ft_free_ptr((void *) &ms);
}
