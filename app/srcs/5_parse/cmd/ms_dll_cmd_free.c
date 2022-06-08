/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dll_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/08 01:45:11 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_dll_cmd_free(t_cmd *cmds)
{
	if (cmds == NULL)
		return ;
	cmds = ms_dll_cmd_last(cmds);
	while (cmds->prev != NULL)
	{
		ft_free_ptr((void *) &cmds->path_and_name);
		ft_free_ptr((void *) &cmds->error_msg);
		ft_free_ptr((void *) &cmds->just_name);
		ft_free_ptr((void *) &cmds->cmd_line);
		ft_mtx_free((void **) cmds->cmd_splited_by_space);
		ft_free_ptr((void *) &cmds);
		cmds = cmds->prev;
	}
	ft_free_ptr((void *) &cmds->path_and_name);
	ft_free_ptr((void *) &cmds->error_msg);
	ft_mtx_free((void **) cmds->cmd_splited_by_space);
	ft_free_ptr((void *) &cmds->cmd_line);
	ft_free_ptr((void *) &cmds);
}
