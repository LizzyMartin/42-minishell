/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/08/18 12:15:18 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_unset(t_ms *ms, t_cmd *current_cmd)
{
	char	*key;

	key = current_cmd->cmd_splited_by_space[1];
	ms_delete_env(ms, key);
	
}
