#include <minishell.h>

void	ms_free(t_ms *ms)
{
	ft_dll_cmd_free(ms);
	ft_free_ptr((void *) ms->p.rl_p);
	ft_free_ptr((void *) ms->p.line);
	ft_mtx_free((void **) ms->p.line_splited);
	ft_free_ptr((void *) ms->p.cmds);
}
