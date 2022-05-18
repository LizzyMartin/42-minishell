/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/17 19:40:54 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cmd_add_back(t_cmd *cmd, char *name)
{
	t_cmd	*last;

	if (cmd == NULL)
	{
		cmd = (t_cmd *) malloc(sizeof(t_cmd));
		cmd->prev = NULL;
		cmd->next = NULL;
	}
	else
	{
		last = ft_cmd_last(cmd);
		cmd->next = (t_cmd *) malloc(sizeof(t_cmd));
		cmd->next->prev = last;
		cmd->next->next = NULL;
	}
	cmd->name = name;
}
