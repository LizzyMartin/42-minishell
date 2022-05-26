/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:37 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 19:41:37 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	last_cmd_exit_code(t_ms *ms)
{
	t_history	*code;

	code = ms_last_history(ms->history);
	ft_putstr_fd(code->l_c_exit_code, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ms_error(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	char	**cmd_splited;

	cmd_splited = current_cmd->cmd_splited_by_space;
	if (ft_strncmp(cmd_splited[1], "$?", 2) == 0)
	{
		last_cmd_exit_code(ms);
		return ;
	}
}
