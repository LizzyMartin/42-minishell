#include <minishell.h>

int main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = ms_init(argc, argv, envp);
	while (1)
		minishell(ms);
	return (0);
}
