/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_read_input_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relizabe <relizabe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/29 21:53:14 by relizabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ctrl_d_exit_shell(int sig, siginfo_t *siginfo, void *context)
{
	ft_printf_to_fd(1, "\n");
	ms_finish(g_ms);
	(void) siginfo;
	(void) sig;
	(void) context;
}

void	ctrl_c_redisplay_prompt(int sig, siginfo_t *siginfo, void *context)
{
	ft_printf("\n");
	if (g_ms->here_doc_open == 0 && \
g_ms->input_command_open == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	(void) siginfo;
	(void) sig;
	(void) context;
}

void	ft_sigation(int signum, void (*f)(int, siginfo_t *, void *))
{
	struct sigaction	sigstruct;

	ft_memset(&sigstruct, '\0', sizeof(sigstruct));
	sigstruct.sa_sigaction = f;
	sigstruct.sa_flags = SA_SIGINFO;
	if (sigaction(signum, &sigstruct, NULL) < 0)
	{
		ft_printf("SIGNAL ERROR!\n");
		return ;
	}
}

void	ms_init_signal_detection(void)
{
	ft_sigation(SIGINT, &ctrl_c_redisplay_prompt);
	signal(SIGQUIT, SIG_IGN);
}
