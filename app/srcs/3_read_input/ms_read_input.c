#include <minishell.h>

void	ms_print_sh_name()
{
	char 	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s%s%s ▸ %s", SHELL, BOLD_CYAN, cwd, WHITE);
	else
		ft_printf("%s%s", SHELL, WHITE);
}

int	ms_read_input(t_ms *ms)
{
	ms_print_sh_name();
	ms_read_input_signals();
	ms->p.line = readline(ms->p.rl_p);
	if (!ms->p.line)
	{
		ctrl_d_exit_shell(SIGQUIT);
		ms->exit_code = 1;
		exit (0);
	}
	else if (*(ms->p.line) == '\0')
	{
		ft_printf("\n");
		return (1);
	}
	ms_print_sh_name();
	return (0);  
}
