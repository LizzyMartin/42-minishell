/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dll_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:44:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/14 00:40:54 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_history	*ms_last_history(t_history *history)
{
	t_history *tmp;

	tmp = history;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
