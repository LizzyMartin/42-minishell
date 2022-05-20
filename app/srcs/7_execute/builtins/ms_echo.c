#include <minishell.h>

int	ms_echo(t_ms *ms)
{
	int i;
	int	has_flag;

	i = 0;
	if(!ms->p.line_splited[1])
	{
		ft_printf("\n");
		return (0);
	}
	has_flag = ft_strncmp(ms->p.line_splited[1], "-n", ft_strlen(ms->p.line_splited[1]));
	while(i++ < ms->p.cmds_size)
	{
		if (ms->p.line_splited[i] && ms->p.line_splited[i][0] == '$')
		{
			if (is_in_env(ms, ms->p.line_splited[i]++) == 1)
				ft_printf("%s", find_env_value(ms, ms->p.line_splited[i]));
		}
		else
		{
			ft_printf("%s", ms->p.line_splited[i]);
		}
	}
	if (has_flag)
		ft_printf("\n");
	ms->p.cmds->exit_status = 0;
	return (ms->p.cmds->exit_status);
}
