/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:21:16 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_add_env(t_ms *ms, char *key, char *value)
{
	t_env	*aux;

	aux = ms->envs;
	if (!aux)
	{
		aux = (t_env *) malloc(sizeof(struct s_env));
		aux->key = key;
		aux->value = value;
		aux->next = NULL;
		aux->prev = NULL;
	}
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = (t_env *) malloc(sizeof(struct s_env));
		aux->next->key = key;
		aux->next->value = value;
		aux->next->next = NULL;
		aux->next->prev = aux;
	}
}
