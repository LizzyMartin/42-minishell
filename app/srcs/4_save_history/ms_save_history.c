#include <minishell.h>

void	save_history(t_ms *ms)
{
	ms->p.cmds->exit_status = 0;
}
