#include <minishell.h>

int	ms_parse(t_ms *ms)
{
	ms->line_splited = ft_split(ms->line, ' ');
	ms->args_size = ft_mtx_size((void **) ms->line_splited) - 1;
	return (ms->exit_status);
}
