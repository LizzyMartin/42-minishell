#include <minishell.h>

void	ms_read_input(t_ms *ms)
{
	char 	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s%s%s ▸ %s", SHELL, BOLD_CYAN, cwd, WHITE);
	else
		ft_printf("%s%s", SHELL, WHITE);
	ms->p.line = readline(ms->p.rl_p);
	if (!ms->p.line)
		exit (EXIT_SUCCESS);
	ms_signals(ms);
}
