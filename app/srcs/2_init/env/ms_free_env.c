/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:00:23 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:24:50 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free_env(t_ms *ms)
{
	t_env	*aux;
	t_env	*tmp;

	aux = ms->envs;
	while (aux)
	{
		if (ms->envs->key)
			free(ms->envs->key);
		if (ms->envs->value)
			free(ms->envs->value);
		tmp = aux->next;
		free(aux);
		aux = tmp;
	}
	ms->envs = NULL;
}
