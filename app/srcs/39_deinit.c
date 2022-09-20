/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39_deinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grupo_capela <grupo_capela@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/20 17:26:02 by grupo_capel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	ms_finish_aux(t_ms *ms)
{
	if (ms->tmp != NULL)
		ft_free_ptr((void *) &ms->tmp);
	if (ms->tmp2 != NULL)
		ft_free_ptr((void *) &ms->tmp2);
	if (ms->aux != NULL)
		ft_free_ptr((void *) &ms->aux);
	if (ms->shell_line)
		ft_free_ptr((void *) &ms->shell_line);
	if (ms->p)
		ms_free_prompt(ms);
	if (ms->shell_line_tokenized)
		ft_free_ptr((void *) &ms->shell_line_tokenized);
	if (ms->readline_var)
		ft_free_ptr((void *) &ms->readline_var);
	ft_free_ptr((void *) &ms->connectors_order);
	if (ms->qs)
		ft_free_ptr((void *) &ms->qs);
	if (ms)
		ft_free_ptr((void *) &ms);
}

void	ms_finish(t_ms *ms)
{
	ft_free_ptr((void *) &ms->connectors_order);
	rl_replace_line("", 0);
	rl_on_new_line();
	ms_free_history(ms);
	clear_history();
	rl_clear_history();
	ms_free_env(ms->envs);
	ms_free_env(ms->aux_envs);
	ms_finish_aux(ms);
	get_next_line(-1);
}

void	ms_reinit(t_ms *ms)
{
	ms->p_amount = 1;
	ms->input_command_open = 0;
	ms_free_prompt(ms);
	ft_free_ptr((void *) &ms->tmp);
	ft_free_ptr((void *) &ms->tmp2);
	ft_free_ptr((void *) &ms->aux);
	ft_free_ptr((void *) &ms->sh_name);
	ft_free_ptr((void *) &ms->shell_line);
	ft_free_ptr((void *) &ms->qs);
	ft_free_ptr((void *) &ms->connectors_order);
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ft_mtx_free((void **) ms->slt_splited_by_connectors);
}
