/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:54:01 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/09 21:05:01 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_curr_prompt(t_p *curr_prompt)
{
	while (curr_prompt->next != NULL)
		curr_prompt = curr_prompt->next;
	while (curr_prompt->prev)
	{
		if (curr_prompt->next->cmds != NULL)
			ms_dll_cmd_free(curr_prompt->next->cmds);
		if (curr_prompt->next->this_p_line != NULL)
			ft_free_ptr((void *) &curr_prompt->next->this_p_line);
		if (curr_prompt->next->this_p_line_splited_by_pipe != NULL)
			ft_free_ptr((void *) \
				&curr_prompt->next->this_p_line_splited_by_pipe);
		if (curr_prompt->next->output_path != NULL)
			ft_free_ptr((void *) &curr_prompt->next->output_path);
		if (curr_prompt->next != NULL)
			ft_free_ptr((void *) &curr_prompt->next);
		curr_prompt = curr_prompt->prev;
	}
}

void	ms_free_prompt(t_ms *ms, t_p *curr_prompt)
{
	free_curr_prompt(curr_prompt);
	if (ms->p == NULL)
		return ;
	if (ms->p->cmds != NULL)
		ms_dll_cmd_free(ms->p->cmds);
	if (ms->p->this_p_line != NULL)
		ft_free_ptr((void *) &ms->p->this_p_line);
	if (ms->p->this_p_line_splited_by_pipe != NULL)
		ft_free_ptr((void *) &ms->p->this_p_line_splited_by_pipe);
	if (ms->p->output_path != NULL)
		ft_free_ptr((void *) &ms->p->output_path);
	if (ms->p != NULL)
		ft_free_ptr((void *) &ms->p);
}
