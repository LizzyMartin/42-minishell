#include <minishell.h>

int	ms_export(t_ms *ms)
{
	int	 i;
	char **envp;

	i = 0;
	envp = ms->envp;
	while (envp[i])
	{
		i++;
	}
	envp[i] = ms->p.line;
	ms->envp = envp;
	ms->p.cmds->exit_status = 0;
	return (ms->p.cmds->exit_status);
}
