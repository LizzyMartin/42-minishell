/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:34 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/02 20:25:14 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_env(t_ms *ms)
{
	t_env	*env;

	env = ms->envs;
	while (env)
	{
		if (env->key != NULL && env->value != NULL)
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	ms->p->cmds->exit_code = EXIT_SUCCESS;
}
