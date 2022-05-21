#include <minishell.h>

int	ms_echo(t_ms *ms, t_cmd *current_cmd)
{
	int i;
	int has_flag;
	char **cmd_splited = ms->p.line_splited;
	char *no_dolar;

	if (current_cmd)
	{
	}
	i = 0;
	if(!cmd_splited[1])
	{
		ft_printf("\n");
		return (0);
	}
	if (ft_strncmp(cmd_splited[1], "$?", 2) == 0)
	{
		last_cmd_exit_status(ms);
		return (0);
	}
	has_flag = ft_strncmp(cmd_splited[1], "-n", ft_strlen(cmd_splited[1]));
	while(i++ < ms->p.cmds_size)
	{
		if (cmd_splited[i] && cmd_splited[i][0] == '$')
		{
			no_dolar = ft_substr(cmd_splited[1], 1, ft_strlen(cmd_splited[1]));
			if (is_in_env(ms, no_dolar) == 1)
				ft_printf("%s", find_env_value(ms, no_dolar));
		}
		else
			ft_printf("%s", cmd_splited[i]);
	}
	if (has_flag)
		ft_printf("\n");
	ms->p.cmds->exit_status = 0;
	return (ms->p.cmds->exit_status);
}
