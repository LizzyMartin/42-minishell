/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_commands_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 20:04:15 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *current_cmd)
{
	if (current_cmd == NULL)
		return (0);
	else if (ft_strncmp(current_cmd, "$?", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "exit", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "echo", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "pwd", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "cd", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "export", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "unset", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "env", ft_strlen(current_cmd)) == 0)
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
		ft_putstr_fd("bash: ", 1);
		last_cmd_exit_code(ms);
		ft_putstr_fd(E_CMDNOTFOUND, 1);
	}
	else if (ft_strncmp(name, "exit", ft_strlen(name)) == 0)
		ms_exit(current_cmd, prompt);
	else if (ft_strncmp(name, "echo", ft_strlen(name)) == 0)
		ms_echo(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "pwd", ft_strlen(name)) == 0)
		ms_pwd(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "cd", ft_strlen(name)) == 0)
		ms_cd(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "export", ft_strlen(name)) == 0)
		ms_export(ms, current_cmd, prompt);
	else if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
		ms_unset(ms, current_cmd);
	else if (ft_strncmp(name, "env", ft_strlen(name)) == 0)
		ms_env(ms, current_cmd, prompt);
}

void	ms_close_fds(t_p *curr_prompt)
{
	if (curr_prompt->input_fd > 0)
		close(curr_prompt->input_fd);
	if (curr_prompt->output_fd > 1)
		close(curr_prompt->output_fd);
}
