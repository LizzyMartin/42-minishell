/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28_execute_commands_utils_3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/12 01:22:03 by acapela-         ###   ########.fr       */
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
			{
				ft_pf_error("miniheaven: %s %s", \
				current_cmd->path_and_name, E_NOTDIR);
				current_cmd->exit_code = 127;
			}
			else
				perror("miniheaven: ");
			exit(127);
		}
	}
	return (child_process_id);
}

int	cmd_not_found(t_cmd *current_cmd, t_p *curr_prompt)
{
	char	*tmp;

	if (current_cmd->index == 0 && curr_prompt->has_here_doc)
		return (1);
	tmp = ft_strtrim(current_cmd->cmd_line, " ");
	current_cmd->cmd_line = \
ft_str_replace_all(current_cmd->cmd_line, T_SPACE, " ");
	ft_pf_error("miniheaven: %s %s\n", tmp, E_CMDNOTFOUND);
	ft_free_ptr((void *) &tmp);
	(void) curr_prompt;
	return (1);
}

int	cmd_rounded_by_quote(t_ms *ms, t_p *curr_prompt)
{
	int		len;
	char	*tmp;
	char	**split;

	len = ft_strlen(ms->shell_line);
	tmp = curr_prompt->this_p_line;
	split = ft_split_by_str(tmp, T_SPACE);
	if ((ms->shell_line[0] == '"' && ms->shell_line[len - 1] == '"')
		|| (ms->shell_line[0] == '\'' && \
		ms->shell_line[len - 1] == '\''))
	{
		len = ft_mtx_size((void **) split);
		ft_mtx_free((void **) split);
		if (len <= 1)
			return (0);
		else
			return (1);
	}
	ft_mtx_free((void **) split);
	return (0);
}

int	ms_which_command_type(t_p *curr_prompt, \
t_cmd *current_cmd, t_ms *ms)
{
	if (cmd_rounded_by_quote(ms, curr_prompt))
		return (cmd_not_found(current_cmd, curr_prompt));
	if (ft_strncmp(current_cmd->just_name, "history", 7) == 0)
	{
		ms_add_history(ms, curr_prompt->this_p_line);
		ms_print_history(ms, current_cmd, curr_prompt);
		if (current_cmd->index == (curr_prompt->args_amount - 1))
			return (1);
	}
	else if (is_builtin(current_cmd->just_name))
	{
		execute_builtin(ms, current_cmd, curr_prompt);
	}
	else if (current_cmd->can_execute == 1)
	{
		ms_execute_command(curr_prompt, current_cmd, \
			ms->envp, &(curr_prompt->input_fd));
	}
	else
		cmd_not_found(current_cmd, curr_prompt);
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
		waitpid(child_process_id, &current_cmd->exit_code, 0);
		if (current_cmd->exit_code && current_cmd->exit_code != 127)
			current_cmd->exit_code = WEXITSTATUS(current_cmd->exit_code);
	}
	if (*aux_fd > 2)
		close (*aux_fd);
	*aux_fd = prompt->pipe[0];
	(void) child_process_id;
	close(prompt->pipe[1]);
}
