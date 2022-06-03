/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:39 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/02 20:18:04 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_exit(t_cmd *current_cmd)
{
	int i;

	i = 0;
	current_cmd->exit_code = 0;
	if (current_cmd->args_amount > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("miniheaven: exit: too many arguments\n", 2);
		current_cmd->exit_code = 127;
		return ;
	}
	else if (current_cmd->args_amount == 2)
	{
		while (current_cmd->cmd_splited_by_space[1][i])
		{
			if (!ft_isdigit(current_cmd->cmd_splited_by_space[1][i]))
			{
				ft_pf_error("exit\nminiheaven: exit: %s: numeric argument required\n", current_cmd->cmd_splited_by_space[1]);
				exit(current_cmd->exit_code);
			}
			i++;
		}
		ctrl_d_exit_shell(SIGQUIT);
	}
	else
	{
		ctrl_d_exit_shell(SIGQUIT);
	}
	exit(current_cmd->exit_code);
}
	