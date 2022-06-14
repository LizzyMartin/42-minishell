/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_ctrl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:37:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/14 17:59:18 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	SIGINT: CTRL + C
    SIGQUIT: CTRL + D
	SIG_IGN: ignore signal
*/
void	ctrl_c_redisplay_prompt(int signal)
{
	(void)signal;
	ft_printf("\n");
	if (g_ms->here_doc_open == 0 && \
g_ms->input_command_open == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_d_exit_shell(int signal)
{
	(void)signal;
	ms_finish(g_ms);
	ft_printf_to_fd(1, "exit\n");
}

void	ctrl_d_quit_process(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (Core Dumped)\n", 1);
}
