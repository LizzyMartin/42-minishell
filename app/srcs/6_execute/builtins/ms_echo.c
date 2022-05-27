/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:25 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:50:48 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_cmd_content(t_ms *ms, \
	t_cmd *current_cmd, char **cmd_splited, int aux)
{
	char	*no_dolar;
	int		i;

	i = 0;
	while (i++ < current_cmd->args_amount - 1)
	{
		if (cmd_splited[i] && cmd_splited[i][0] == '$')
		{
			no_dolar = ft_substr(cmd_splited[1], 1, ft_strlen(cmd_splited[1]));
			if (ms_is_in_env(ms, no_dolar) == 1)
				ft_putstr_fd(ms_find_env_value(ms, no_dolar), aux);
		}
		else
			ft_putstr_fd(cmd_splited[i], aux);
		ft_putstr_fd(" ", aux);
	}
}

void	last_cmd_exit_code(t_ms *ms)
{
	t_history	*code;

	code = ms_last_history(ms->history);
	ft_printf("%d\n", code->l_c_exit_code);
}

void	ms_echo(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int		has_flag;
	char	**cmd_splited;
	int		aux;
	int		tmp_fd[2];

	cmd_splited = current_cmd->cmd_splited_by_space;
	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	aux = tmp_fd[1];
	if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	if (!cmd_splited[1])
		ft_putstr_fd("\n", aux);
	else if (ft_strncmp(cmd_splited[1], "$?", 2) == 0)
		last_cmd_exit_code(ms);
	else
	{
		has_flag = ft_strncmp(cmd_splited[1], "-n", ft_strlen(cmd_splited[1]));
		print_cmd_content(ms, current_cmd, cmd_splited, aux);
		if (has_flag)
			ft_putstr_fd("\n", aux);
		ms->p.cmds->exit_code = 0;
		if (aux != 1)
			close(aux);
	}
}
