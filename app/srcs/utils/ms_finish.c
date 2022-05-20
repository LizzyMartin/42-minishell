#include <minishell.h>

void	ms_finish(t_ms *ms)
{
	ft_free_ptr((void *) ms);
}
