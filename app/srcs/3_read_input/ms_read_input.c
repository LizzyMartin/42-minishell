#include <minishell.h>

void	ms_read_input(t_ms *ms)
{
	ft_printf(SHELL);
		ms->p.line = readline(ms->p.rl_p);
		if (!ms->p.line)
			exit (EXIT_SUCCESS);
	ms_signals(ms);
}
