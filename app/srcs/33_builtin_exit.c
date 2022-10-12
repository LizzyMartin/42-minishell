/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:39 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/11 22:15:47 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	ms_check_numeric_argument(t_ms *ms, t_cmd *current_cmd, int aux)
{
	char	*line;
	int		i;
	int		exit_code;

	i = 0;
	while (current_cmd->cmd_splited_by_space[1][i])
	{
		if (!ft_isdigit(current_cmd->cmd_splited_by_space[1][i]))
		{
			line = ft_printf_to_var("exit\nminiheaven: exit: %s: \
numeric argument required\n", \
					current_cmd->cmd_splited_by_space[1]);
			ft_putstr_fd(line, aux);
			ft_free_ptr((void *) &line);
			exit_code = current_cmd->exit_code;
			ms_finish(ms);
			get_next_line(-1);
			exit(exit_code);
		}
		i++;
	}
}

void	ms_exit(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int		aux;
	int		exit_code;
	int		clo;

	clo = 0;
	aux = bridge_builtion_other_cmds(current_cmd, prompt, &clo);
	current_cmd->exit_code = 0;
	if (current_cmd->args_amount > 2)
	{
		ft_putstr_fd("exit\nminiheaven: exit: too many arguments\n", aux);
		current_cmd->exit_code = 127;
		return ;
	}
	else if (current_cmd->args_amount == 2)
		ms_check_numeric_argument(ms, current_cmd, aux);
	exit_code = current_cmd->exit_code;
	if (clo)
		close(aux);
	if (current_cmd->index == (prompt->args_amount - 1))
	{
		exit_code = current_cmd->exit_code;
		ft_putstr_fd("exit\n", aux);
		ms_finish(ms);
		get_next_line(-1);
		exit(exit_code);
	}
}
