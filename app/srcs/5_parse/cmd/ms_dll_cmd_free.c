/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dll_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 22:52:33 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_dll_cmd_free(t_cmd *cmds)
{
	t_cmd	*free;
	t_cmd	*last;

	if (cmds == NULL)
		return ;
	cmds = ms_dll_cmd_last(cmds);
	while (cmds->prev != NULL)
	{
		last = cmds;
		free = last;
		ft_free_ptr((void *) &free->path_and_name);
		ft_free_ptr((void *) &free->error_msg);
		ft_free_ptr((void *) &free->just_name);
		ft_free_ptr((void *) &free->cmd_line);
		ft_mtx_free((void **) free->cmd_splited_by_space);
		cmds = cmds->prev;
		ft_free_ptr((void *) &free);
	}
	free = cmds;
	ft_free_ptr((void *) &free->path_and_name);
	ft_free_ptr((void *) &free->error_msg);
	ft_mtx_free((void **) free->cmd_splited_by_space);
	ft_free_ptr((void *) &free->cmd_line);
	ft_free_ptr((void *) &free);
	cmds = NULL;
}
