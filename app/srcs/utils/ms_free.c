#include <minishell.h>

void	ms_free(t_ms *ms)
{
	ft_free_ptr((void *) ms->readline_var);
	ft_free_ptr((void *) ms->shell_line);	
	ft_free_ptr((void *) &(ms->p));
}
