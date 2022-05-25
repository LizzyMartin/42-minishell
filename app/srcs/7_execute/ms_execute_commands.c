#include <minishell.h>

static void	ms_execute_command(t_p *prompt, t_cmd *current_cmd, char **envp, int *aux_fd)
{
	int	bridge_between_processes[2];
	int	child_process_id;

	pipe(bridge_between_processes);
	child_process_id = fork();
	ms_while_executing_commands_signals();
	if (child_process_id == 0)
	{
		 dup2(*aux_fd, 0);
		 if ((prompt->pipe_amount - 1) == current_cmd->index)
		 	dup2(prompt->output_fd, 1);
		 else
		 	dup2(bridge_between_processes[1], 1);

		if (execve(current_cmd->path_and_name, current_cmd->cmd_splited_by_space, envp)
		== -1)
			perror("erro no execve");
	}
	if ((prompt->pipe_amount - 1) == current_cmd->index)
	{
		waitpid(child_process_id, &current_cmd->exit_code, 0);
	}
	if (*aux_fd > 2)
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
		execute_builtin(ms, current_cmd, prompt);
	else
	{
		// char **tmp = malloc(sizeof(char *));
		// tmp[0] = ft_strdup("ls");
		// int pid = fork();
		// if (pid == 0)
		// {
		// 	if (execve("/usr/bin/ls", tmp , ms->envp) == -1)
		// 		perror("erro:");
		// }
		// if (pid != 0)
		// 	wait(NULL);

		// if (0)
		// {
			prompt->aux_fd = prompt->input_fd;
			while (current_cmd)
			{
				ms_execute_command(prompt, current_cmd, ms->envp, &(prompt->aux_fd));
				current_cmd = current_cmd->next;
			}
		//}
	}
}

void       ms_execute(t_ms *ms)
{
	t_p *curr_prompt;
	int	o_here_doc;

	curr_prompt = &ms->p;
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
	if (curr_prompt->only_input_redirected_to_file == 1)
	     return ;


	while (curr_prompt)
	{
		ms_execute_commands(ms, curr_prompt);
		//ft_printf("%s", ms_dll_cmd_last(curr_prompt->cmds)->just_name);
		ms_add_history(ms, NULL, curr_prompt->cmds);
		curr_prompt = curr_prompt->next;
	}
}
