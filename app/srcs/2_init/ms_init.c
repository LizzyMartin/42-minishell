/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:07 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:26:58 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ms	*ms_init(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = (t_ms *) malloc(sizeof(t_ms));
	ms->exit_code = 0;
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = envp;
	ms->history = NULL;
	ms->p_amount = 1;
	ms_init_env(ms);
	ms_init_history(ms);
	system("clear");
	print_banner();
	return (ms);
}
