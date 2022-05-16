#include <minishell.h>

int	minishell(int argc, char **argv, char **envp)
{
	t_ms	*ms;
	char	*prompt;
	char	*line;

	ms = (t_ms *) malloc(sizeof(t_ms));
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = envp;
	prompt = NULL;
	system("clear");
	ms_banner();
	while (1)
	{
		ft_printf("\033[1m\033[34m$minishell: \033[0m");
		line = readline(prompt);
		ms->line = line;
		if (parse(ms) == 0)
			execute(ms);
	}
	return (ms->exit_status);
}
