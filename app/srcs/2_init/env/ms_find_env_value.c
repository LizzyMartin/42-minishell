/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_env_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/07 15:33:50 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ms_find_env_value(t_ms *ms, char *key)
{
	t_env	*env;
	t_env	*aux_envs;

	env = ms->envs;
	aux_envs = ms->aux_envs;
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			&& (env->key != NULL && env->value != NULL))
			return (env->value);
		env = env->next;
	}
	while (aux_envs)
	{
		if ((ft_strncmp(ft_strtrim(aux_envs->key, " "), \
				key, ft_strlen(aux_envs->key)) == 0)
			&& (aux_envs->key != NULL && aux_envs->value != NULL))
			return (aux_envs->value);
		aux_envs = aux_envs->next;
	}
	return (NULL);
}
