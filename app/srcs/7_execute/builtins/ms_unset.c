#include <minishell.h>

int		ms_unset(t_ms *ms)
{
	char	*cmd;

	cmd = ms->p.line_splited[1];
	delete_env(ms, cmd);
	return (ms->p.cmds->exit_status);
}
