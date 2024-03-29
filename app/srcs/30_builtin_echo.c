/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:25 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/13 00:07:12 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	print_cmd_content(t_ms *ms, \
	t_cmd *current_cmd, char **cmd_splited, int aux)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd_splited[1], "-n", ft_strlen(cmd_splited[1])) == 0)
		i = 1;
	while (!ft_strncmp(cmd_splited[i], "-n", \
	ft_strlen(cmd_splited[i])) && cmd_splited[i])
		++i;
	if (i != 0)
		i--;
	while (i++ < current_cmd->args_amount - 1)
	{
		if (ms->has_single_quotes)
			ft_chr_remove_all(cmd_splited[i], '\'');
		cmd_splited[i] = ft_str_replace_all(cmd_splited[i], T_SPACE, " ");
		cmd_splited[i] = ft_str_replace_all(cmd_splited[i], T_HC1, "<<");
		cmd_splited[i] = ft_str_replace_all(cmd_splited[i], T_HC2, "<");
		cmd_splited[i] = ft_str_replace_all(cmd_splited[i], T_SUBSHELL, "()");
		ft_putstr_fd(cmd_splited[i], aux);
		if (i != current_cmd->args_amount - 1)
			ft_putstr_fd(" ", aux);
	}
}

void	last_cmd_exit_code(t_ms *ms)
{
	t_history	*code;

	code = ms_last_history(ms->history);
	(void) code;
}

static void	ms_echo_having_flag(t_ms *ms, char **cmd_splited, \
	t_cmd *current_cmd, int aux)
{
	int		has_flag;

	has_flag = ft_strncmp(cmd_splited[1], "-n", ft_strlen(cmd_splited[1]));
	print_cmd_content(ms, current_cmd, cmd_splited, aux);
	if (has_flag)
		ft_putstr_fd("\n", aux);
	ms->p->cmds->exit_code = 0;
}

void	ms_echo(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	char	**cmd_splited;
	int		aux;
	int		clo;

	clo = 0;
	aux = bridge_builtion_other_cmds(current_cmd, prompt, &clo);
	cmd_splited = current_cmd->cmd_splited_by_space;
	if (!cmd_splited[1])
		ft_putstr_fd("\n", aux);
	else if (ft_strncmp(cmd_splited[1], "$?", 2) == 0)
		ft_putstr_fd("\n", aux);
	else
		ms_echo_having_flag(ms, cmd_splited, current_cmd, aux);
	if (clo)
		close(aux);
}
