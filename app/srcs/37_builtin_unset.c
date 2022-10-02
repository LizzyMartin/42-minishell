/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relizabe <relizabe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/01 22:06:12 by relizabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_unset(t_ms *ms, t_cmd *current_cmd)
{
	char	*key;

	key = current_cmd->cmd_splited_by_space[1];
	if (key)
		ms_delete_env(ms, key);
}
