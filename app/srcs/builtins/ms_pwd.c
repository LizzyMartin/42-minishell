#include <minishell.h>

int ms_pwd(t_ms *ms)
{
	char cwd[1000];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ms->p.cmds->exit_status = 0;
		ft_printf("%s\n", cwd);
	}
	else
	{
		ms->p.cmds->exit_status = 1;
	}
	return (ms->p.cmds->exit_status);
}
