/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:54:01 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/04 03:55:49 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free_prompt(t_p *curr_prompt)
{
	t_p	*tmp;

	while (curr_prompt)
	{
		tmp = curr_prompt;
		ms_dll_cmd_free(tmp->cmds);
		curr_prompt = curr_prompt->next;
		ft_free_ptr((void *) &tmp);
	}
}
