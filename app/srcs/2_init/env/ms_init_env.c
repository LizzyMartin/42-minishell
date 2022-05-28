/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:10 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/28 01:17:49 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_init_env(t_ms *ms)
{
	int		i;
	char	**envp;
	char	**envp_splitted;

	i = 0;
	envp = ms->envp;
	ms->envs = (t_env *) malloc(sizeof(t_env));
	if (ms->envp != NULL)
	{
		while (envp[i])
		{
			envp_splitted = ft_split(envp[i], '=');
			if (envp_splitted[0] != NULL && envp_splitted[1] != NULL)
				ms_add_env(ms, envp_splitted[0], envp_splitted[1]);
			ft_mtx_free((void **) envp_splitted);
			i++;
		}
	}
}
