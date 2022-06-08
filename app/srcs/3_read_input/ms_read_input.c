/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:47 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/08 00:54:14 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ms_print_sh_name(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_printf_to_var("%s%s%s%s%s%s ", \
            BOLD_BLUE, SHELL, END_COLOR, BOLD_CYAN, cwd, END_COLOR));
	else
		return (ft_printf_to_var("%s", SHELL));
}

int	ms_read_input(t_ms *ms)
{
	ms->sh_name = ms_print_sh_name();
	ms_read_input_signals();
	ms->shell_line = readline(ms->sh_name);
	ft_free_ptr((void *) &ms->sh_name);
	if (!ms->shell_line)
	{
		ctrl_d_exit_shell(SIGQUIT);
		exit(0);
	}
	else if (*(ms->shell_line) == '\0')
		return (1);
	return (0);
}
