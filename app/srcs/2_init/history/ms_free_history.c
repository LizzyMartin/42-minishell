/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:51:51 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 21:52:07 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free_history(t_ms *ms)
{
	t_history	*head;

	head = ms->history;
	while (head->next != NULL)
		head = head->next;
	while (head->prev != NULL)
	{
		head = head->prev;
		if (head->next != NULL)
			ft_free_ptr((void *) &head->next);
	}
	if (head != NULL)
		ft_free_ptr((void *) &head);
}
