/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_env_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relizabe <relizabe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:39:40 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/27 22:11:35 by relizabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	update_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(env->key)) == 0) && \
			(env->key != NULL && env->value != NULL))
		{
			ft_free_ptr((void *) &env->value);
			env->value = ft_strdup(value);
		}
		env = env->next;
	}
}
