#include <minishell.h>

t_ms	*ms_init(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = (t_ms *) malloc(sizeof(t_ms));
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = envp;
	ms->prompt = NULL;
	system("clear");
	ft_printf(BANNER);
	return (ms);
}
