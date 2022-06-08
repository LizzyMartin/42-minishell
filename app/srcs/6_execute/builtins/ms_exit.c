/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:39 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/08 19:05:29 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ms_check_numeric_argument(t_cmd *current_cmd, int aux)
{
	char	*line;
	int		i;

	i = 0;
	while (current_cmd->cmd_splited_by_space[1][i])
	{
		if (!ft_isdigit(current_cmd->cmd_splited_by_space[1][i]))
		{
			line = ft_printf_to_var("exit\nminiheaven: exit: %s: \
				numeric argument required\n", \
					current_cmd->cmd_splited_by_space[1]);
			ft_putstr_fd(line, aux);
			exit(current_cmd->exit_code);
		}
		i++;
	}
}

void	ms_exit(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int		aux;
	int		tmp_fd[2];
	int		exit_code;

	current_cmd->exit_code = 0;
	if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	else
	{
		pipe(tmp_fd);
		prompt->input_fd = tmp_fd[0];
		aux = tmp_fd[1];
	}
	if (current_cmd->args_amount > 2)
	{
		ft_putstr_fd("exit\nminiheaven: exit: too many arguments\n", aux);
		current_cmd->exit_code = 127;
		return ;
	}
	else if (current_cmd->args_amount == 2)
		ms_check_numeric_argument(current_cmd, aux);
	exit_code = current_cmd->exit_code;
	ms_finish(ms);
	if (aux != 1)
	{
		close (tmp_fd[0]);
		close (tmp_fd[1]);
	}
	exit(exit_code);
}
