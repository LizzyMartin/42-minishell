/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_ctrl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:37:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 15:55:22 by argel            ###   ########.fr       */
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
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c_interrupt_process(int signal)
{
	(void)signal;
	g_ms->here_doc_open = 0;
	ft_putstr_fd("\n", 1);
}

void	ctrl_d_exit_shell(int signal)
{
	(void)signal;
	if (g_ms->here_doc_open == 1)
	{
		ft_printf_to_fd(1, "miniheaven: warning: here-document at line 5 delimited by end-of-file (wanted `FIM')\n");

		
	}
	ms_finish(g_ms);
	ft_printf("exit\n");
}

void	ctrl_d_quit_process(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (Core Dumped)\n", 1);
}
