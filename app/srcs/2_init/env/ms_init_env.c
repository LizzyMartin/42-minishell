/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:10 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 15:11:50 by argel            ###   ########.fr       */
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
	envp_splitted = NULL;
	if (ms->envp != NULL)
	{
		envp_splitted = ft_split(envp[i], '=');
		while (envp[i])
		{
			if (envp_splitted[0] != NULL && envp_splitted[1] != NULL)
				ms_add_env(ms, envp_splitted[0], envp_splitted[1]);
			i++;
			ft_mtx_free((void **) envp_splitted);
			envp_splitted = ft_split(envp[i], '=');
		}
	}
	ft_mtx_free((void **) envp_splitted);
}
