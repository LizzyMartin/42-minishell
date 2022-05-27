/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:39 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 15:37:29 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_error(char *const *cmd_splited, int i)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(cmd_splited[i], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(1);
}

void	ms_exit(t_ms *ms, t_cmd *current_cmd)
{
	char	**cmd_splited;
	int		i;

	i = 1;
	cmd_splited = current_cmd->cmd_splited_by_space;
	if (!cmd_splited[1])
		exit(0);
	while (cmd_splited[i])
	{
		if (!ft_isdigit((int)cmd_splited[i][0]))
		{
			ms->p->cmds->exit_code = 2;
			print_error(cmd_splited, i);
		}
		i++;
	}
	if (i > 2)
	{
		ms->p->cmds->exit_code = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	exit(ms->p->cmds->exit_code);
}
