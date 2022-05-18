#include <minishell.h>

int	minishell(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = ms_init(argc, argv, envp);
	while (1)
	{
		ft_printf(SHELL);
		ms->p.line = readline(ms->p.rl_p);
		if (!ms->p.line)
			exit (EXIT_SUCCESS);
		ms_signals(ms);
		ms_parse(ms);
		ms_execute(ms);
	}
	return (ms->p.cmds->exit_status);
}
