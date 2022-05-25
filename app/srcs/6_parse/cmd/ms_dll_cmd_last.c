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

t_cmd	*ms_dll_cmd_last(t_cmd *cmds)
{
	t_cmd *tmp;

	tmp = cmds;
	if (tmp == NULL)
		return (tmp);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
