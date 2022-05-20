#include <minishell.h>

int		is_builtin(char *current_cmd)
{
	if (current_cmd == NULL)
		return (0);
	else if (ft_strncmp(current_cmd, "echo", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "pwd", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "cd", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "export", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "unset", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "env", ft_strlen(current_cmd)) == 0)
		return (1);
	else if (ft_strncmp(current_cmd, "exit", ft_strlen(current_cmd)) == 0)
		return (1);
	else
		return (0);
}

void	execute_builtin(t_ms *ms, t_cmd *current_cmd)
{
	char *name;

	name = current_cmd->name;
	if (ft_strncmp(name, "echo", ft_strlen(name)) == 0)
		ms_echo(ms);
	else if (ft_strncmp(name, "pwd", ft_strlen(name)) == 0)
		ms_pwd(ms);
	else if (ft_strncmp(name, "cd", ft_strlen(name)) == 0)
		ms_cd(ms);
	else if (ft_strncmp(name, "export", ft_strlen(name)) == 0)
		ms_export(ms);
	else if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
		ms_unset(ms);
	else if (ft_strncmp(name, "env", ft_strlen(name)) == 0)
		ms_env(ms);
	else if (ft_strncmp(name, "exit", ft_strlen(name)) == 0)
		ms_exit(ms);
}
