/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:00:23 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 15:16:14 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free_env(t_ms *ms)
{
	t_env *head;
	t_env *del;

	del = NULL;
	head = ms->envs;
	if (head == NULL)
		return ;
	else
	{		
		while (head->next != NULL)
			head = head->next;
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
		ft_printf("limpou tudo");
	}
}
