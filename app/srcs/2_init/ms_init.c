#include <minishell.h>

t_ms	*ms_init(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = (t_ms *) malloc(sizeof(t_ms));
	ms->exit_code = 0;
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = envp;
	ms->p.h = NULL;
	init_env(ms);
	ms_init_h(ms);
	system("clear");
	print_banner();
	return (ms);
}
