/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/13 00:37:45 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_unset(t_ms *ms, t_cmd *current_cmd)
{
	char	*key;

	key = current_cmd->cmd_splited_by_space[1];
	if (ft_mtx_size((void **) current_cmd->cmd_splited_by_space) <= 1)
		return ;
	if (key)
	{
		ms_delete_env(&ms->envs, key);
		ms_delete_env(&ms->aux_envs, key);
	}
}
