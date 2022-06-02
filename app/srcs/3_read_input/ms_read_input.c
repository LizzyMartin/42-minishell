/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:47 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/02 01:12:31 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ms_print_sh_name(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_printf_to_var("%s%s%s%s ▸ %s", \
			BOLD_BLUE, SHELL, BOLD_CYAN, cwd, WHITE));
	else
		return (ft_printf_to_var("%s%s", SHELL, WHITE));
}

int	ms_read_input(t_ms *ms)
{
	ms->readline_var = ms_print_sh_name();
	ms_read_input_signals();
	ms->shell_line = readline(ms->readline_var);
	if (!ms->shell_line || ft_strncmp(ms->shell_line, \
			"exit", 4) == 0)
	{
		ctrl_d_exit_shell(SIGQUIT);
		exit(0);
	}
	else if (*(ms->shell_line) == '\0')
	{
		ft_printf("\n");
		return (1);
	}
	return (0);
}
