/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:00:20 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:25:10 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

int	ms_is_in_env(t_ms *ms, const char *key)
{
	t_env	*aux;

	aux = ms->envs;
	while (aux)
	{
		if (!ft_strncmp(aux->key, key, ft_strlen(aux->key)))
			return (1);
		aux = aux->next;
	}
	aux = ms->aux_envs;
	while (aux)
	{
		if (!ft_strncmp(aux->key, key, ft_strlen(aux->key)))
			return (1);
		aux = aux->next;
	}
	return (0);
}
