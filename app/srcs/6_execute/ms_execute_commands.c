/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:42:02 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/07 00:09:56 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	ms_execv(t_ms *ms, t_p *curr_prompt, t_cmd *current_cmd)
{
	if (ms->is_cat_sequence == 1
		&& ft_strnstr(current_cmd->just_name, \
		"cat", ft_strlen(current_cmd->just_name)) != NULL)
	{
		current_cmd = current_cmd->next;
		return (1);
	}
	if (ms_which_command_type(curr_prompt, \
	current_cmd, ms) == 1)
		return (0);
	return (-1);
}

int	ms_execute_commands_loop(t_ms *ms, t_p *curr_prompt, t_cmd *current_cmd)
{
	int	child;
	int	res;

	res = -1;
	if (current_cmd->subshell)
	{
		child = fork();
		if (child == 0)
		{
			res = ms_execv(ms, curr_prompt, current_cmd);
			exit(0);
		}
		waitpid(-1, NULL, 0);
	}
	else
		res = ms_execv(ms, curr_prompt, current_cmd);
	return (res);
}

int	ms_execute_commands(t_ms *ms, t_p *curr_prompt)
{
	t_cmd	*current_cmd;
	int		res;

	res = -1;
	current_cmd = NULL;
	current_cmd = curr_prompt->cmds;
	pre_cat_ls_sc(ms, curr_prompt);
	while (current_cmd)
	{
		res = ms_execute_commands_loop(ms, curr_prompt, current_cmd);
		if (res == 0)
			return (0);
		else if (res == 1)
			continue ;
		current_cmd = current_cmd->next;
	}
	exec_cat_ls_sc(ms);
	ms_add_history(ms, NULL, curr_prompt->cmds);
	ms_close_fds(curr_prompt);
	current_cmd = ms_dll_cmd_last(curr_prompt->cmds);
	waitpid(-1, NULL, 0);
	return (current_cmd->exit_code);
}

void	ms_execute(t_ms *ms)
{
	t_p	*curr_prompt;
	int	o_here_doc;

	curr_prompt = ms->p;
	if (curr_prompt->has_here_doc == 1)
	{
		o_here_doc = curr_prompt->only_here_doc;
		curr_prompt->input_fd = ms_here_doc(ms, curr_prompt);
		if (o_here_doc == 1)
		{
			close(curr_prompt->input_fd);
			return ;
		}
	}
	print_fd_or_execute_cmd(ms, curr_prompt);
}
