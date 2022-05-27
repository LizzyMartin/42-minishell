/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 15:20:27 by argel            ###   ########.fr       */
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
