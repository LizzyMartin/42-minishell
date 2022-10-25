/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:00:20 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/12 21:41:14 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<_minishell.h>

int	ms_is_in_env(t_ms *ms, const char *key)
{
	t_env	*aux;
	char	*tmp;

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
		tmp = ft_strtrim(aux->key, " ");
		if (!ft_strncmp(tmp, key, ft_strlen(aux->key)))
		{
			ft_free_ptr((void *) &tmp);
			return (1);
		}
		ft_free_ptr((void *) &tmp);
		aux = aux->next;
	}
	return (0);
}
