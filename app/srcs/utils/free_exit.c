#include <minishell.h>

void    free_exit(t_ms *ms)
{
	ft_mtx_free((void **)ms->line_splited);
	exit (ms->exit_status);
}
