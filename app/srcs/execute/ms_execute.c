#include <minishell.h>

void	ms_execute(t_ms *ms)
{
	char	*cmd;

	cmd = ms->line_splited[0];
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
	else
    {
        ft_printf("\033[1m\033[34m$minishell: \033[0m");
	    ft_printf("\033[1m\033[30m%s\033[0m: command  not found\n", cmd);
		ms->exit_status = 1;
    }
}
