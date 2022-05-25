/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_cmd_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/18 17:18:26 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_dll_cmd_free(t_ms *ms)
{
	t_cmd *cmds = ms->p.cmds;
	t_cmd *last;

	if (cmds == NULL)
		return ;
	while (cmds->next != NULL)
		cmds = cmds->next;
	while (cmds->prev != NULL)
	{
		last = cmds;
		ft_free_ptr((void *) last->name_and_path);
		ft_free_ptr((void *) last->error_msg);
		ft_free_ptr((void *) last->name);
		ft_mtx_free((void **) last->cmd_splited);
		cmds = cmds->prev;
	}
}
