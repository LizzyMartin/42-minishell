/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:34 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 15:36:48 by argel            ###   ########.fr       */
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
