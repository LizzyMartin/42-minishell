/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39_deinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/28 20:02:18 by acapela-         ###   ########.fr       */
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


static void	ms_free_subshells(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->n_subs)
	{
		ms_finish((void *) &ms->subs[i]);
		i++;
	}
}

void	ms_finish(t_ms *ms)
{
	ft_free_ptr((void *) &ms->connectors_order);
	ms_free_history(ms);
	ms_free_env(ms->envs);
	ms_free_env(ms->aux_envs);
	ms_finish_aux(ms);
	clear_history();
	rl_clear_history();
}

void	ms_reinit(t_ms *ms)
{
	ms->p_amount = 1;
	ms->input_command_open = 0;
	ms->i_subs = 0;
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
	ms_free_subshells(ms);
}
