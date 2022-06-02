/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:42:02 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/01 20:58:02 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_child_process_id(const t_p *prompt, \
	t_cmd *current_cmd, char **envp, const int *aux_fd)
{
	int	child_process_id;

	child_process_id = fork();
	ms_while_executing_commands_signals();
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
				ft_pf_error("miniheaven: %s %s", current_cmd->path_and_name, E_NOTDIR);
			else
				perror("miniheaven: ");
			current_cmd->exit_code = 1;
		}
	}
	return (child_process_id);
}

static void	ms_execute_command(t_p *prompt, \
	t_cmd *current_cmd, char **envp, int *aux_fd)
{
	int	child_process_id;

	pipe(prompt->pipe);
	child_process_id = get_child_process_id(prompt, current_cmd, envp, aux_fd);
	if ((prompt->pipe_amount - 1) == current_cmd->index)
		waitpid(child_process_id, &current_cmd->exit_code, 0);
	if (*aux_fd > 2)
		close (*aux_fd);
	*aux_fd = prompt->pipe[0];
	close(prompt->pipe[1]);
}

void	ms_execute_commands(t_ms *ms, t_p *curr_prompt)
{
	t_cmd	*current_cmd;

	current_cmd = curr_prompt->cmds;
	while (current_cmd)
	{
		if (ft_strncmp(current_cmd->just_name, "history", 7) == 0)
		{
			ms_add_history(ms, NULL, curr_prompt->cmds);
			ms_print_history(ms);
			return ;
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
		current_cmd = current_cmd->next;
	}
	ms_add_history(ms, NULL, curr_prompt->cmds);
	ms_close_fds(curr_prompt);
}

static void	print_fd_or_execute_cmd(t_ms *ms, t_p *curr_prompt)
{
	if (curr_prompt->only_input_redirected_to_file == 1)
		return ;
	else if (curr_prompt->no_cmd_just_redirect == 1)
		ft_fd_dup2(curr_prompt->pipe_here_doc[0], curr_prompt->output_fd);
	else
	{
		while (curr_prompt)
		{
			ms_execute_commands(ms, curr_prompt);
			curr_prompt = curr_prompt->next;
		}
	}
}

void	ms_execute(t_ms *ms)
{
	t_p	*curr_prompt;
	int	o_here_doc;

	curr_prompt = ms->p;
	if (curr_prompt->has_here_doc == 1)
	{
		o_here_doc = curr_prompt->only_here_doc;
		curr_prompt->input_fd = ms_here_doc(curr_prompt);
		if (o_here_doc == 1)
		{
			close(curr_prompt->input_fd);
			return ;
		}
	}
	print_fd_or_execute_cmd(ms, curr_prompt);
}
