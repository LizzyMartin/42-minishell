/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_ctrl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:37:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:37:55 by acapela-         ###   ########.fr       */
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
	ms_print_sh_name();
}

void	ctrl_c_interrupt_process(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
}

void	ctrl_d_exit_shell(int signal)
{
	(void)signal;
	ft_printf("exit\n");
}

void	ctrl_d_quit_process(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (Core Dumped)\n", 1);
}