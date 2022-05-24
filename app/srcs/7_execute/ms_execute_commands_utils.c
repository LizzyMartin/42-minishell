#include <minishell.h>

void	last_cmd_exit_code(t_ms *ms)
{
	// t_cmd *tmp;

	// tmp = ms->p.cmds;
	// while (tmp->next != NULL)
	// 	tmp = tmp->next;
	// ft_printf("%d\n", tmp->exit_code);
	if (ms)
	{
	}
}

int		is_builtin(char *current_cmd)
{
	if (current_cmd == NULL)
		return (0);
	else if (ft_strncmp(current_cmd, "exit", ft_strlen(current_cmd)) == 0)
		return (1);
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
	else
		return (0);
}

void	execute_builtin(t_ms *ms, t_cmd *current_cmd)
{
	char *name;

	name = current_cmd->just_name;
	if (ft_strncmp(name, "exit", ft_strlen(name)) == 0)
		ms_exit(ms);
	else if (ft_strncmp(name, "echo", ft_strlen(name)) == 0)
		ms_echo(ms, current_cmd);
	else if (ft_strncmp(name, "pwd", ft_strlen(name)) == 0)
		ms_pwd(ms);
	else if (ft_strncmp(name, "cd", ft_strlen(name)) == 0)
		ms_cd(ms, current_cmd);
	else if (ft_strncmp(name, "export", ft_strlen(name)) == 0)
		ms_export(ms, current_cmd);
	else if (ft_strncmp(name, "unset", ft_strlen(name)) == 0)
		ms_unset(ms, current_cmd);
	else if (ft_strncmp(name, "env", ft_strlen(name)) == 0)
		ms_env(ms);
}
