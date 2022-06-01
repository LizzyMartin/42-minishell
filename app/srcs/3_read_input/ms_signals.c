/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 21:47:16 by acapela-         ###   ########.fr       */
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
