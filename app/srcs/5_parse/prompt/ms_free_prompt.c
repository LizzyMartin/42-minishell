/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:54:01 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/06 21:50:02 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free_prompt(t_p *curr_prompt)
{
	while (curr_prompt->next != NULL)
		curr_prompt = curr_prompt->next;
	while (curr_prompt->prev)
	{
		ms_dll_cmd_free(curr_prompt->next->cmds);
		ft_free_ptr((void *) &curr_prompt->next->output_path);
		ft_free_ptr((void *) &curr_prompt->next);
		curr_prompt = curr_prompt->prev;
	}
	ms_dll_cmd_free(curr_prompt->cmds);
	ft_free_ptr((void *) &curr_prompt->output_path);
	ft_free_ptr((void *) &curr_prompt);
}
