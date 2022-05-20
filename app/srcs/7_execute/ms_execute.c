#include <minishell.h>

static void	ms_execute_commands(t_ms *ms, t_cmd *current_cmd , int *tmp_fd)
{
	int	bridge_between_processes[2];
	int	child_process_id;

	pipe(bridge_between_processes);
	child_process_id = fork();
	if (child_process_id == 0)
	{
		dup2(*tmp_fd, 0);
		dup2(bridge_between_processes[1], 1);
		if (execve(current_cmd->name_and_path, ms->p.line_splited, ms->envp)
		== -1)
			perror("");
	}
	if ((ms->p.cmds_size - 1) == current_cmd->index)
		waitpid(child_process_id, &current_cmd->exit_status, 0);
	close (*tmp_fd);
	*tmp_fd = bridge_between_processes[0];
	close(bridge_between_processes[1]);
}

void		ms_execute(t_ms *ms)
{
	t_cmd	*current_cmd;
	int		tmp_fd;

	current_cmd = ms->p.cmds;
	if (is_builtin(current_cmd->name) == 1)
	{
		execute_builtin(ms, current_cmd);
	}
	else
	{
		while (current_cmd)
		{
			tmp_fd = current_cmd->std_in;
			ms_execute_commands(ms, current_cmd, &tmp_fd);
			ft_fd_print(tmp_fd);
			current_cmd = current_cmd->next;
		}
	}
}
