/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_delete_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:45 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/02 03:16:24 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

void	free_aux(t_env **del)
{
	ft_free_ptr((void *) &(*del)->key);
	ft_free_ptr((void *) &(*del)->value);
	ft_free_ptr((void *) &(*del));
}

void	ms_delete_env(t_ms *ms, char *key)
{
	t_env	*env;
	t_env	*del;

	del = NULL;
	env = ms->envs;
	while (env)
	{
		if ((env->key != NULL && env->value != NULL))
		{
			if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			{
				del = env;
				if (env->next != NULL)
				{
					env->prev->next = env->next;
					env->next->prev = env->prev;
				}
				else
					env->prev->next = NULL;
				free_aux(&del);
				break ;
			}
		}
		env = env->next;
	}
}
