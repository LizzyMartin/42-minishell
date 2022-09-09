/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:57 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_reinit(t_ms *ms)
{
	int	i;

	i = 0;
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
	while (ms->n_subs > 0)
	{
		ms_finish(&ms->subs[i]);
		ms->n_subs--;
	}
}
