/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:57 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/02 15:27:37 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_reinit(t_ms *ms)
{
	ms->p_amount = 1;
	ms_free_prompt(ms->p);
	ft_free_ptr((void *) &ms->readline_var);
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ft_mtx_free((void **) ms->slt_splited_by_connectors);
	rl_replace_line("", 0);
	rl_on_new_line();
}
