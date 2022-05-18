#include <minishell.h>

int	ms_unset(t_ms *ms)
{
	return (ms->p.cmds->exit_status);
}
