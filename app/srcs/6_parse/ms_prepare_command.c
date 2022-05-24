#include <minishell.h>

char	*append_path(t_cmd *current_cmd, t_ms *ms)
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
				path[i], current_cmd->just_name);
		if (access(path_plus_command, X_OK) == 0)
		{
			return (path_plus_command);
		}
	}
	current_cmd->error_msg = "command not found";
	current_cmd->exit_code = 1;
	return (NULL);
}
