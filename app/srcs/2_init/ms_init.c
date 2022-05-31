/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:07 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/30 20:26:34 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_ms_is_being_executed = 1;

void	ms_init(t_ms **ms, int argc, char **argv, char **envp)
{
	(*ms) = (t_ms *) ft_calloc(1, sizeof(t_ms));
	(*ms)->argc = argc;
	(*ms)->argv = argv;
	(*ms)->envp = envp;
	(*ms)->exit_code = 0;
	(*ms)->history = NULL;
	(*ms)->envs = NULL;
	(*ms)->p_amount = 1;
	(*ms)->history_i = 0;
	(*ms)->shell_line = NULL;
	(*ms)->shell_line_tokenized = NULL;
	(*ms)->slt_splited_by_connectors = NULL;
	(*ms)->readline_var = NULL;
	(*ms)->p = NULL;
	
	ms_init_env(*ms);
	ms_init_history(*ms);
	system("clear");
	print_banner();
}

/*typedef struct s_minishell
{
	int						argc;
	char					**argv;
	char					**envp;
	char					*shell_line;
	char					*shell_line_tokenized;
	char					**slt_splited_by_connectors;
	char					*readline_var;
	int						p_amount;
	t_p						*p;
	int						exit_code;
	int						history_i;
	t_history				*history;
	t_env					*envs;
}	t_ms;*/
