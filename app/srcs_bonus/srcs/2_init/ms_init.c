/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:07 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	ms_init_aux(t_ms *ms)
{
	ms->is_aux_env = 0;
	ms->slt_splited_by_connectors = NULL;
	ms->readline_var = NULL;
	ms->p = NULL;
	ms->connectors_index = 0;
	ms->connectors_amount = 0;
	ms->connectors_order = NULL;
	ms->here_doc_open = 0;
	ms->no_path = 0;
	ms->i_subs = 0;
}

void	ms_init(t_ms *ms, int argc, char **argv, char **envp)
{
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = envp;
	ms->exit_code = 0;
	ms->history = NULL;
	ms->envs = NULL;
	ms->p_amount = 1;
	ms->history_i = 0;
	ms->shell_line = NULL;
	ms->shell_line_tokenized = NULL;
	ms->has_double_quotes = 0;
	ms->has_single_quotes = 0;
	ms_init_aux(ms);
	ms_init_env(ms);
	ms_init_history(ms);
}
