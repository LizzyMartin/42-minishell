#include <minishell.h>

int		is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (1);
	else
		return (0);
}

void	execute_builtin(t_ms *ms)
{
	char *cmd;

	cmd = ms->p.line_splited[0];
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		ms_echo(ms);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		ms_pwd(ms);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		ms_cd(ms);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		ms_export(ms);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		ms_unset(ms);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		ms_env(ms);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		ms_exit(ms);
}
