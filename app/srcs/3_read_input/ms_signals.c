/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 16:02:07 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Signals while ms is reading input */
void	ms_read_input_signals(void)
{
	signal(SIGINT, ctrl_c_redisplay_prompt);
	signal(SIGQUIT, ctrl_d_exit_shell);
}

/* Signals while some process is being executed  */
void	ms_while_executing_commands_signals(void)
{
	signal(SIGINT, ctrl_c_interrupt_process);
	signal(SIGQUIT, ctrl_d_quit_process);
}

void	ms_while_executing_commands_signals(t_sigaction *action, void (*handler)(int), int sig)
{
	action->sa_handler = handler;
	action->sa_flags = SA_RESTART;
	sigemptyset(&action->sa_mask);
	sigaction(sig, action, NULL);
}