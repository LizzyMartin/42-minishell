/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:47 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:18:35 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_print_sh_name(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s%s%s%s ▸ %s", BOLD_BLUE, SHELL, BOLD_CYAN, cwd, WHITE);
	else
		ft_printf("%s%s", SHELL, WHITE);
}

int	ms_read_input(t_ms *ms)
{
	ms_print_sh_name();
	ms_read_input_signals();
	ms->shell_line = readline(ms->readline_var);
	if (!ms->shell_line || ft_strncmp(ms->shell_line, "exit", 4) == 0)
	{
		ctrl_d_exit_shell(SIGQUIT);
		ms->exit_code = 1;
		exit (0);
	}
	else if (*(ms->shell_line) == '\0')
	{
		ft_printf("\n");
		return (1);
	}
	return (0);
}
