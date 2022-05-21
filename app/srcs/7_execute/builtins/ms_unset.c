#include <minishell.h>

int		ms_unset(t_ms *ms)
{
	char	*key;

	key = ms->p.line_splited[1];
	delete_env(ms, key);
	return (ms->p.cmds->exit_status);
}
