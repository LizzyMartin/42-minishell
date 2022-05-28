/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dll_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 22:18:18 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_dll_cmd_free(t_cmd *cmds)
{
	t_cmd 	*free;
	t_cmd	*last;

	if (cmds == NULL)
		return ;
	while (cmds->next != NULL)
		cmds = cmds->next;
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
//		ft_free_ptr((void *) &free->just_name);
		ft_free_ptr((void *) &free->cmd_line);
		ft_free_ptr((void *) &free);
	cmds = NULL;
}
