#include <minishell.h>

void	last_cmd_exit_code(t_ms *ms)
{
	t_history *code;

	code = ms_last_history(ms->history);
	ft_printf("%d\n", code->l_c_exit_code);
}

void	ms_echo(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int i;
	int has_flag;
	char **cmd_splited = current_cmd->cmd_splited_by_space;
	char *no_dolar;

	i = 0;
	if(!cmd_splited[1])
	{
		ft_putstr_fd("\n", prompt->output_fd);
		return ;
	}
	if (ft_strncmp(cmd_splited[1], "$?", 2) == 0)
	{
		last_cmd_exit_code(ms);
		return ;
	}
	has_flag = ft_strncmp(cmd_splited[1], "-n", ft_strlen(cmd_splited[1]));
	while(i++ < current_cmd->args_amount - 1)
	{
		if (cmd_splited[i] && cmd_splited[i][0] == '$')
		{
			no_dolar = ft_substr(cmd_splited[1], 1, ft_strlen(cmd_splited[1]));
			if (is_in_env(ms, no_dolar) == 1)
				ft_putstr_fd(find_env_value(ms, no_dolar), prompt->output_fd);
		}
		else
			ft_putstr_fd(cmd_splited[i], prompt->output_fd);
		ft_putstr_fd(" ", prompt->output_fd);
	}
	if (has_flag)
		ft_putstr_fd("\n", prompt->output_fd);
	ms->p.cmds->exit_code = 0;
}
