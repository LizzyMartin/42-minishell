/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26_execute_commands_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relizabe <relizabe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/26 20:18:08 by relizabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	is_builtin(char *current_cmd)
{
	if (current_cmd == NULL)
		return (0);
	else if (ft_strncmp(current_cmd, "$?", 2) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "env", 3) == 0)
		return (1);
	else
		return (0);
}

void	execute_builtin(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	char	*name;

	name = current_cmd->just_name;
	if (ft_strncmp(name, "$?", ft_strlen(name)) == 0)
	{
		ft_putstr_fd("miniheaven: ", 1);
		last_cmd_exit_code(ms);
		ft_putstr_fd(E_CMDNOTFOUND, 1);
		ft_putstr_fd("\n", 1);
	}
	else if (ft_strncmp(name, "exit", 4) == 0)
		ms_exit(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "echo", 4) == 0)
		ms_echo(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "pwd", 3) == 0)
		ms_pwd(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "cd", 2) == 0)
		ms_cd(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "export", 6) == 0)
		ms_export(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "unset", 5) == 0)
		ms_unset(ms, current_cmd);
	else if (ft_strncmp(name, "env", 3) == 0)
		ms_env(ms, current_cmd, prompt);
}

static int	pipe_fd(t_p *prompt, int tmp_fd[])
{
	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	return (tmp_fd[1]);
}

int	bridge_builtion_other_cmds(t_cmd *current_cmd, t_p *prompt, int *clo)
{
	int		tmp_fd[2];
	int		aux;

	if ((current_cmd->index == prompt->args_amount - 1) \
	&& prompt->output_fd > 0)
		aux = prompt->output_fd;
	else if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	else
	{
		aux = pipe_fd(prompt, tmp_fd);
		*clo = 1;
	}
	return (aux);
}
