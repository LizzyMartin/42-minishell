/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_commands_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/07 19:45:33 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ms_which_command_type(t_p *curr_prompt, \
t_cmd *current_cmd, t_ms *ms)
{
	if (ft_strncmp(current_cmd->just_name, "history", 7) == 0)
	{
		ms_add_history(ms, NULL, curr_prompt->cmds);
		ms_print_history(ms);
		return (1);
	}
	else if (is_builtin(current_cmd->just_name) == 1)
		execute_builtin(ms, current_cmd, curr_prompt);
	else if (current_cmd->can_execute == 1)
	{
		ms_execute_command(curr_prompt, current_cmd, \
			ms->envp, &(curr_prompt->input_fd));
	}
	else
		ft_printf_to_fd(1, "miniheaven: %s %s", \
			current_cmd->just_name, current_cmd->error_msg);
	return (0);
}

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
