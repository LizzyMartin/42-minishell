#include <minishell.h>

void	ms_pwd(t_ms *ms)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ms->p.cmds->exit_code = 0;
		ft_printf("%s\n", cwd);
	}
	else
		ms->p.cmds->exit_code = 1;
}
