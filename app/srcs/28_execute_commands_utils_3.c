/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28_execute_commands_utils_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 19:47:53 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	get_child_process_id(const t_p *prompt, \
	t_cmd *current_cmd, char **envp, const int *aux_fd)
{
	int	child_process_id;

	child_process_id = fork();
	if (child_process_id == 0)
	{
		dup2(*aux_fd, 0);
		if ((prompt->pipe_amount - 1) == current_cmd->index)
			dup2(prompt->output_fd, 1);
		else
			dup2(prompt->pipe[1], 1);
		if (execve(current_cmd->path_and_name, \
			current_cmd->cmd_splited_by_space, envp) == -1)
		{
			if (current_cmd->cmd_is_path_but_invalid == 1)
				ft_pf_error("miniheaven: %s %s", \
				current_cmd->path_and_name, E_NOTDIR);
			else
				perror("miniheaven: ");
			current_cmd->exit_code = 1;
		}
	}
	return (child_process_id);
}

int	ms_which_command_type(t_p *curr_prompt, \
t_cmd *current_cmd, t_ms *ms)
{
	if (ft_strncmp(current_cmd->just_name, "history", 7) == 0)
	{
		ms_add_history(ms, NULL, curr_prompt->cmds);
		ms_print_history(ms, current_cmd, curr_prompt);
		if (current_cmd->index == (curr_prompt->args_amount - 1))
			return (1);
	}
	else if (is_builtin(current_cmd->just_name) == 1)
	{
		execute_builtin(ms, current_cmd, curr_prompt);
	}
	else if (current_cmd->can_execute == 1)
	{
		ms_execute_command(curr_prompt, current_cmd, \
			ms->envp, &(curr_prompt->input_fd));
	}
	else
	{
		ft_printf_to_fd(1, "miniheaven: %s %s\n", \
			current_cmd->just_name, current_cmd->error_msg);
		return (1);
	}
	return (0);
}

void	ms_execute_command(t_p *prompt, \
t_cmd *current_cmd, char **envp, int *aux_fd)
{
	int	child_process_id;

	pipe(prompt->pipe);
	child_process_id = get_child_process_id(prompt, current_cmd, envp, aux_fd);
	if ((prompt->pipe_amount - 1) == current_cmd->index)
	{
		waitpid(-1, &current_cmd->exit_code, 0);
		if (current_cmd->exit_code)
		current_cmd->exit_code = WEXITSTATUS(current_cmd->exit_code);
	}
	if (*aux_fd > 2)
		close (*aux_fd);
	*aux_fd = prompt->pipe[0];
	close(prompt->pipe[1]);
}
