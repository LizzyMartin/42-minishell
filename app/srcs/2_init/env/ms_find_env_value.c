/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_find_env_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:31:29 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	return (ft_strdup(""));
}
