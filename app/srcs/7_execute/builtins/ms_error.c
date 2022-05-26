#include <minishell.h>

void	last_cmd_exit_code(t_ms *ms)
{
	t_history *code;

	code = ms_last_history(ms->history);
	ft_printf("%d: command not found\n", code->l_c_exit_code);
}

void	ms_error(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	int i;
	int has_flag;
	char **cmd_splited = current_cmd->cmd_splited_by_space;
	char *no_dolar;
	int	aux;
	int	tmp_fd[2];

	if (ft_strncmp(cmd_splited[1], "$?", 2) == 0)
	{
		last_cmd_exit_code(ms);
		return ;
	}
}
