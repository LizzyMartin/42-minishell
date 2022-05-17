#include <minishell.h>

int	minishell(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = ms_init(argc, argv, envp);
	while (1)
	{
		ft_printf(SHELL);
		ms->line = readline(ms->prompt);
		ms_signals(ms);
		ms_parse(ms);
		ms_execute(ms);
	}
	return (ms->exit_status);
}
