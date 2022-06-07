/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:42:02 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/07 19:45:39 by acapela-         ###   ########.fr       */
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
				ft_pf_error("miniheaven: %s %s", \
				current_cmd->path_and_name, E_NOTDIR);
			else
				perror("miniheaven: ");
			current_cmd->exit_code = 1;
		}
	}
	return (child_process_id);
}

void	ms_execute_command(t_p *prompt, \
t_cmd *current_cmd, char **envp, int *aux_fd)
{
	int	child_process_id;

	pipe(prompt->pipe);
	child_process_id = get_child_process_id(prompt, current_cmd, envp, aux_fd);
	if ((prompt->pipe_amount - 1) == current_cmd->index)
	{
		waitpid(child_process_id, &current_cmd->exit_code, 0);
		if (current_cmd->exit_code)
		current_cmd->exit_code = WEXITSTATUS(current_cmd->exit_code);
	}
	if (*aux_fd > 2)
		close (*aux_fd);
	*aux_fd = prompt->pipe[0];
	close(prompt->pipe[1]);
}

int	ms_execute_commands(t_ms *ms, t_p *curr_prompt)
{
	t_cmd	*current_cmd;

	current_cmd = curr_prompt->cmds;
	while (current_cmd)
	{
		if (ms_which_command_type(curr_prompt, \
		current_cmd, ms) == 1)
			return (0);
		current_cmd = current_cmd->next;
	}
	cat_ls_sc(curr_prompt);
	ms_add_history(ms, NULL, curr_prompt->cmds);
	ms_close_fds(curr_prompt);
	current_cmd = ms_dll_cmd_last(curr_prompt->cmds);
	return (current_cmd->exit_code);
}

static void	print_fd_or_execute_cmd(t_ms *ms, t_p *curr_prompt)
{
	int	i;
	int	exit_code;

	i = 0;
	if (curr_prompt->only_input_redirected_to_file == 1)
		return ;
	else if (curr_prompt->no_cmd_just_redirect == 1)
		ft_fd_dup2(curr_prompt->pipe_here_doc[0], curr_prompt->output_fd);
	else
	{
		while (curr_prompt)
		{
			exit_code = ms_execute_commands(ms, curr_prompt);
			if (ms->connectors_order != NULL)
			{
				if (ms->connectors_order[i] == 1 && exit_code != 0)
					break ;
				else if (ms->connectors_order[i] == 2 && exit_code == 0)
					break ;
			}
			i++;
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
