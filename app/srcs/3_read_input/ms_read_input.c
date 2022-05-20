#include <minishell.h>

int	ms_read_input(t_ms *ms)
{
	char 	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s%s%s ▸ %s", SHELL, BOLD_CYAN, cwd, WHITE);
	else
		ft_printf("%s%s", SHELL, WHITE);
	ms_signals(ms);
	ms->p.line = readline(ms->p.rl_p);
	if (ms->p.rl_p == NULL && ft_str_is_empty(ms->p.line) == 1)
	{
		ft_printf("\n");
		return (1);
	}
	return (0);  
}
