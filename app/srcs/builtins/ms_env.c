#include <minishell.h>

int	ms_env(t_ms *ms)
{
	int		i;
	char	**envp;

	i = 0;
	envp = ms->envp;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	ms->p.cmds->exit_status = 0;
	return (ms->p.cmds->exit_status);
}
