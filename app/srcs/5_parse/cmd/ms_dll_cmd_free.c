/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dll_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/08 19:00:26 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_dll_cmd_free(t_cmd *cmds)
{
	while (cmds->next != NULL)
		cmds = cmds->next;
	while (cmds->prev != NULL)
	{
		if (cmds->next->path_and_name)
			ft_free_ptr((void *) &cmds->next->path_and_name);
		if (cmds->next->error_msg)
			ft_free_ptr((void *) &cmds->next->error_msg);
		if (cmds->next->just_name)
			ft_free_ptr((void *) &cmds->next->just_name);
		if (cmds->next->cmd_line)
			ft_free_ptr((void *) &cmds->next->cmd_line);
		if (cmds->next->cmd_splited_by_space)
			ft_mtx_free((void **) cmds->next->cmd_splited_by_space);
		if (cmds->next)
			ft_free_ptr((void *) &cmds->next);
		cmds = cmds->prev;
	}
	if (cmds->path_and_name)
		ft_free_ptr((void *) &cmds->path_and_name);
	if (cmds->error_msg)
		ft_free_ptr((void *) &cmds->error_msg);
	if (cmds->just_name)
		ft_free_ptr((void *) &cmds->just_name);
	if (cmds->cmd_line)
		ft_free_ptr((void *) &cmds->cmd_line);
	if (cmds->cmd_splited_by_space)
		ft_mtx_free((void **) cmds->cmd_splited_by_space);
	if (cmds)
		ft_free_ptr((void *) &cmds);
}
