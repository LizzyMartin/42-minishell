#include <minishell.h>

void	ms_exit(t_ms *ms)
{
	int	i;

	i = 1;
	ms->exit_status = 0;
	if (!ms->line_splited[1])
		free_exit(ms);
	while (ms->line_splited[i])
	{
		if (!ft_isdigit((int) ms->line_splited[i][0]))
		{
			ms->exit_status = 2;
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(ms->line_splited[i], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_exit(ms);
		}
		i++;
	}
	if (i > 2)
	{
		ms->exit_status = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	free_exit(ms);
}
