#include <minishell.h>

void	ms_exit(t_ms *ms)
{
	ctrl_d_exit_shell(SIGQUIT);
	ms->exit_code = 1;
	exit (0);
	// int i;

	// i = 1;
	// if (!ms->p.line_splited[1])
	// 	exit(0);
	// while (ms->p.line_splited[i])
	// {
	// 	if (!ft_isdigit((int) ms->p.line_splited[i][0]))
	// 	{
	// 		ms->p.cmds->exit_status = 2;
	// 		ft_putstr_fd("exit\nminishell: exit: ", 2);
	// 		ft_putstr_fd(ms->p.line_splited[i], 2);
	// 		ft_putstr_fd(": numeric argument required\n", 2);
	// 		exit(1);
	// 	}
	// 	i++;
	// }
	// if (i > 2)
	// {
	// 	ms->p.cmds->exit_status = 1;
	// 	ft_putstr_fd("exit: too many arguments\n", 2);
	// 	return ;
	// }
	// exit(ms->p.cmds->exit_status);
}
