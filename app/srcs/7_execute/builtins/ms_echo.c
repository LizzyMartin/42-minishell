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
	int	aux;

	pipe(prompt->builtin_bridge);
	prompt->input_fd = prompt->builtin_bridge[0];
	aux = prompt->builtin_bridge[1];
	if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	i = 0;
	if(!cmd_splited[1])
	{
		ft_putstr_fd("\n", aux);
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
				ft_putstr_fd(find_env_value(ms, no_dolar), aux);
		}
		else
			ft_putstr_fd(cmd_splited[i], aux);
		ft_putstr_fd(" ", aux);
	}
	if (has_flag)
		ft_putstr_fd("\n", aux);
	ms->p.cmds->exit_code = 0;
	if (aux != 1)
		close(aux);
}
