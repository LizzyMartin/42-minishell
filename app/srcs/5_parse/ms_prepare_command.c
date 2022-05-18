#include <minishell.h>

static char	*append_path(t_cmd *current_cmd, t_ms *ms)
{
	char	**path;
	char	*path_plus_command;
	int		i;

	i = -1;
	while (*(ms->envp))
		if (ft_strnstr(*(ms->envp), "PATH=", sizeof(*(ms->envp))))
			break ;
	else
			ms->envp++;
	path = ft_split(*(ms->envp), ':');
	while (path[++i])
	{
		path_plus_command = ft_printf_to_var("%s/%s",
				path[i], current_cmd->name);
		if (access(path_plus_command, X_OK) == 0)
		{
			return (path_plus_command);
		}
	}
	current_cmd->error_msg = "comando não encontrado";
	current_cmd->exit_status = 1;
	return (NULL);
}

void	ms_prepare_command (t_ms *ms)
{
	t_cmd	*current_cmd;
	char	**command_splited;

	current_cmd = ms->p.cmds;
	command_splited = NULL;
	current_cmd->name_and_path = append_path(current_cmd, ms);

}
