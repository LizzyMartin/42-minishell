/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:54:01 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/12 19:16:36 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	free_curr_prompt(t_p *curr_prompt)
{
	if(!curr_prompt)
		return ;
	while (curr_prompt->next != NULL)
		curr_prompt = curr_prompt->next;
	while (curr_prompt->prev)
	{
		curr_prompt = curr_prompt->prev;
		if (curr_prompt->next->cmds != NULL)
			ms_dll_cmd_free(curr_prompt->next->cmds);
		if (curr_prompt->next->this_p_line != NULL)
			ft_free_ptr((void *) &curr_prompt->next->this_p_line);
		if (curr_prompt->next->this_p_line_splited_by_pipe != NULL)
			ft_mtx_free((void **) \
				curr_prompt->next->this_p_line_splited_by_pipe);
		if (curr_prompt->next->output_path != NULL)
			ft_free_ptr((void *) &curr_prompt->next->output_path);
		ft_free_ptr((void *) &curr_prompt->next->hd_limiter);
		if (curr_prompt->next->input_fd > 2)
			close(curr_prompt->next->input_fd);
		if (curr_prompt->next->output_fd > 2)
			close(curr_prompt->next->output_fd);
		if (curr_prompt->next != NULL)
			ft_free_ptr((void *) &curr_prompt->next);
	}
}

void	ms_free_prompt(t_ms *ms)
{
	free_curr_prompt(ms->p);
	if (ms->p == NULL)
		return ;
	if (ms->p->cmds != NULL)
		ms_dll_cmd_free(ms->p->cmds);
	if (ms->p->this_p_line != NULL)
		ft_free_ptr((void *) &ms->p->this_p_line);
	if (ms->p->this_p_line_splited_by_pipe != NULL)
		ft_mtx_free((void **) ms->p->this_p_line_splited_by_pipe);
	if (ms->p->output_path != NULL)
		ft_free_ptr((void *) &ms->p->output_path);
	ft_free_ptr((void *) &ms->p->hd_limiter);
	if (ms->p->input_fd > 2)
		close(ms->p->input_fd);
	if (ms->p->output_fd > 2)
		close(ms->p->output_fd);
	if (ms->p != NULL)
		ft_free_ptr((void *) &ms->p);
}
