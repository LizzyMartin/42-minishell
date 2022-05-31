/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/30 23:16:58 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_add_env(t_ms *ms, char *key, char *value)
{
	t_env	*aux;

	aux = ms->envs;
	if (aux->key == NULL)
	{
		aux->key = ft_strdup(key);
		aux->value = ft_strdup(value);
		aux->next = NULL;
		aux->prev = NULL;
	}
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = (t_env *) malloc(sizeof(t_env));
		aux->next->key = ft_strdup(key);
		aux->next->value = ft_strdup(value);
		aux->next->next = NULL;
		aux->next->prev = aux;
	}
}
