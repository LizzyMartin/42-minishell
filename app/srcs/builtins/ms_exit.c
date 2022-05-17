#include <minishell.h>

void	ms_exit(t_ms *ms)
{
	ms->exit_status = 0;
	exit(ms->exit_status);
}
