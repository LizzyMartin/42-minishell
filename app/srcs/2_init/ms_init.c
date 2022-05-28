/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:07 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 22:02:36 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_ms_is_being_executed = 1;

t_ms	*ms_init(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = (t_ms *) ft_calloc(1, sizeof(t_ms));
	ms->exit_code = 0;
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = envp;
	ms->history = NULL;
	ms->p_amount = 1;
	ms->readline_var = NULL;
	ms_init_env(ms);
	ms_init_history(ms);
	system("clear");
	print_banner();
	return (ms);
}
