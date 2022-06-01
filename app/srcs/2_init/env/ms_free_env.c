/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:00:23 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 21:28:38 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free_env(t_ms *ms)
{
	t_env	*head;
	t_env	*del;

	del = NULL;
	head = ms->envs;
	if (head == NULL)
		return ;
	else
	{		
		head = ms_last_env(ms->envs);
		while (head->prev != NULL)
		{
			head = head->prev;
			if (head->next != NULL)
			{
				del = head->next;
				ft_free_ptr((void *) &del->key);
				ft_free_ptr((void *) &del->value);
				ft_free_ptr((void *) &del);
			}
		}
		ft_free_ptr((void *) &head->key);
		ft_free_ptr((void *) &head->value);
		ft_free_ptr((void *) &head);
	}
}
