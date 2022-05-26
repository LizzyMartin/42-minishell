/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:10 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:19:47 by acapela-         ###   ########.fr       */
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
	ms->envs = malloc(sizeof(struct s_env));
	while (envp[i])
	{
		envp_splitted = ft_split(envp[i], '=');
		if (envp_splitted[0] != NULL && envp_splitted[1] != NULL)
			ms_add_env(ms, envp_splitted[0], envp_splitted[1]);
		i++;
	}
}
