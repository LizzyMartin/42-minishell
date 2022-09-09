/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:42:02 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
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

int	ms_execv(t_ms *ms, t_p *curr_prompt, t_cmd *current_cmd)
{
	ft_printf("#%s#\n", current_cmd->cmd_line);
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
			//exit(0);
		}
		// waitpid(child, NULL, 1);
	}
	else
		res = ms_execv(ms, curr_prompt, current_cmd);
	return (res);
}

int	ms_execute_commands(t_ms *ms, t_p *curr_prompt)
{
	t_cmd	*current_cmd;
	int		res;
	int		pid[2];

	res = -1;
	current_cmd = NULL;
	current_cmd = curr_prompt->cmds;
	pre_cat_ls_sc(ms, curr_prompt);
	// create processes if need
	int i = 0;
	pid[0] = fork();
	//
	while (i < 2)
	{
		res = -1;
		if (pid[i] == 0)
		{
			res = ms_execv(ms, curr_prompt, current_cmd);
			current_cmd = current_cmd->next;
			exit(0);
		}
		else
		{
			res = ms_execv(ms, curr_prompt, current_cmd);
		if (res == 0)
			return (0);
		else if (res == 1)
			continue ;
		i++;
		current_cmd = current_cmd->next;
		}
	}
	exec_cat_ls_sc(ms);
	ms_add_history(ms, NULL, curr_prompt->cmds);
	ms_close_fds(curr_prompt);
	current_cmd = ms_dll_cmd_last(curr_prompt->cmds);
	return (current_cmd->exit_code);
}

static void	print_fd_or_execute_cmd_loop(t_ms *ms, t_p *curr_prompt)
{
	int		exit_code;
	char	*tmp;
	int		i;

	i = 0;
	while (curr_prompt)
	{
		tmp = ft_strtrim(curr_prompt->this_p_line, " ");
		if (ft_strncmp(tmp, T_SUBSHELL,
				ft_strlen(curr_prompt->this_p_line)) == 0)
			ms_execute_prompt_in_subshell(ms, curr_prompt, &exit_code);
		else
			exit_code = ms_execute_commands(ms, curr_prompt);
		ft_free_ptr((void *) &tmp);
		if (ms->connectors_order != NULL)
			if ((ms->connectors_order[i] == 1 && exit_code != 0)
				|| (ms->connectors_order[i] == 2 && exit_code == 0))
				break ;
		i++;
		curr_prompt = curr_prompt->next;
	}
}

void	print_fd_or_execute_cmd(t_ms *ms, t_p *curr_prompt)
{
	if (curr_prompt->only_input_redirected_to_file == 1 || \
curr_prompt->only_redirect_to_file == 1)
		return ;
	else if (curr_prompt->no_cmd_just_redirect == 1)
		ft_fd_dup2(curr_prompt->pipe_here_doc[0], curr_prompt->output_fd);
	else
		print_fd_or_execute_cmd_loop(ms, curr_prompt);
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
