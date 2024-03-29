/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:36 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/27 10:22:41 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	update_exit_code_last_cmd(t_ms *ms, t_cmd *cmds, int code)
{
	t_cmd		*tmp;
	int			e_code;
	t_history	*aux;

	aux = ms_last_history(ms->history);
	tmp = ms_dll_cmd_last(cmds);
	if (tmp)
		e_code = tmp->exit_code;
	else
		e_code = 0;
	if (code != -1)
		e_code = code;
	aux->l_c_exit_code = e_code;
	(void) code;
}

static void	ms_add_history_aux(t_ms *ms, t_history *aux,
	char *line)
{
	char		*tmp2;

	aux = ms_last_history(ms->history);
	aux->next = (t_history *) ft_calloc(1, sizeof(struct s_history));
	aux->next->index = ms->history_i;
	if (line != NULL)
		aux->next->line = ft_strdup(line);
	else
	{
		tmp2 = ft_strdup(ms->shell_line);
		aux->next->line = ft_printf_to_var("%s\n", tmp2);
		ft_free_ptr((void *) &tmp2);
	}
	aux->next->next = NULL;
	aux->next->prev = aux;
	aux->next->l_c_exit_code = 127;
}

static void	reset_some_values(t_history *aux)
{
	aux->next = NULL;
	aux->prev = NULL;
	aux->l_c_exit_code = 0;
}

void	ms_add_history(t_ms *ms, char *line)
{
	t_history	*aux;
	t_history	*last_history;

	aux = ms->history;
	ms->history_i++;
	if (!aux)
	{
		aux = (t_history *) ft_calloc(1, sizeof(struct s_history));
		aux->index = ms->history_i;
		if (line != NULL)
			aux->line = ft_strdup(line);
		reset_some_values(aux);
		ms->history = aux;
	}
	else
	{
		last_history = ms_last_history(aux);
		if (!last_history->line && ms->shell_line)
			add_history(ms->shell_line);
		if (last_history->line && ft_strncmp(ms->shell_line,
				last_history->line, ft_strlen(ms->shell_line)))
			add_history(ms->shell_line);
		ms_add_history_aux(ms, aux, line);
	}
}
