/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 15:12:39 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_add_env(t_ms *ms, char *key, char *value)
{
	t_env	*head;

	head = ms->envs;
	if (head == NULL)
	{
		head = malloc (sizeof(t_env));
		head->key = ft_strdup(key);
		head->value = ft_strdup(value);
		head->next = NULL;
		head->prev = NULL;
		ms->envs = head;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = malloc (sizeof(t_env));
		head->next->key = ft_strdup(key);
		head->next->value = ft_strdup(value);
		head->next->next = NULL;
		head->next->prev = head;
	}
}
