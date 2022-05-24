#include <minishell.h>

static void	ms_execute_command(t_p *prompt, t_cmd *current_cmd, char **envp, int *aux_fd)
{
	int	bridge_between_processes[2];
	int	child_process_id;

	pipe(bridge_between_processes);
	child_process_id = fork();
	ms_execute_command_signals();
	if (child_process_id == 0)
	{
		dup2(*aux_fd, 0);
		dup2(bridge_between_processes[1], 1);
		if (execve(current_cmd->path_and_name, current_cmd->cmd_splited_by_space, envp)
		== -1)
		{
			perror("erro no execve");
		}
	}
	if ((prompt->pipe_amount) == current_cmd->index)
		waitpid(child_process_id, &current_cmd->exit_code, 0);
	close (*aux_fd);
	*aux_fd = bridge_between_processes[0];
	close(bridge_between_processes[1]);
}

void		ms_execute_commands(t_ms *ms, t_p *prompt)
{
	t_cmd	*current_cmd;

	current_cmd = prompt->cmds;
	if (ft_strncmp(current_cmd->just_name, "history", 7) == 0)
		ms_print_history(ms);
	else if (is_builtin(current_cmd->just_name) == 1)
		execute_builtin(ms, current_cmd);
	else
	{
		if (prompt->has_here_doc == 1 && (prompt->pipe_amount - 1) >= 0)
		    prompt->input_fd = ms_here_doc(prompt);
		while (current_cmd)
		{
			prompt->aux_fd = prompt->input_fd;
			ms_execute_command(prompt, current_cmd, ms->envp, &(prompt->aux_fd));
			ft_fd_print(prompt->aux_fd);
			current_cmd = current_cmd->next;
		}
	}
}

void       ms_execute(t_ms *ms)
{
	t_p *curr_prompt;

	curr_prompt = &ms->p;
	while (curr_prompt)
	{
		ms_execute_commands(ms, curr_prompt);
		curr_prompt = curr_prompt->next;
	}
}
