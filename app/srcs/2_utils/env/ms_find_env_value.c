/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_env_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relizabe <relizabe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/30 20:26:15 by relizabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

char	*ms_find_aux_env_value(t_ms *ms, char *key)
{
	t_env	*aux_envs;
	char	*trim;

	aux_envs = ms->aux_envs;
	while (aux_envs)
	{
		trim = ft_strtrim(aux_envs->key, " ");
		if ((ft_strncmp(trim, \
				key, ft_strlen(aux_envs->key)) == 0)
			&& (aux_envs->key != NULL && aux_envs->value != NULL))
		{
			ft_free_ptr((void *) &trim);
			return (aux_envs->value);
		}
		ft_free_ptr((void *) &trim);
		aux_envs = aux_envs->next;
	}
	return (NULL);
}

char	*ms_find_env_value(t_ms *ms, char *key)
{
	t_env	*env;

	env = ms->envs;
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			&& (env->key != NULL && env->value != NULL))
			return (env->value);
		env = env->next;
	}
	return (ms_find_aux_env_value(ms, key));
}
