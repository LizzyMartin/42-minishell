/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_delete_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:45 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:21:29 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

void	ms_delete_env(t_ms *ms, char *key)
{
	t_env	*env;

	env = ms->envs;
	while (env)
	{
		if ((env->key != NULL && env->value != NULL))
		{
			if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			{
				if (env->next != NULL)
					env->prev->next = env->next;
				else
					env->prev->next = NULL;
			}
		}
		env = env->next;
	}
}
