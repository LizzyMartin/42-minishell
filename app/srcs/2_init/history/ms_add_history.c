/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:36 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 22:03:33 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ms_add_history_aux(t_ms *ms, t_history	*aux, char *line, t_cmd		*cmds)
{
	t_cmd		*tmp;
	int			e_code;

	tmp = cmds;
	while (aux->next)
		aux = aux->next;
	aux->next = (t_history *) ft_calloc(1, sizeof(struct s_history));
	aux->next->index = ms->history_i;
	if (line != NULL)
		aux->next->line = line;
	else
		aux->next->line = ft_printf_to_var("%s\n", ms->shell_line);
	aux->next->next = NULL;
	aux->next->prev = aux;
	tmp = ms_dll_cmd_last(cmds);
	if (tmp)
		e_code = tmp->exit_code;
	else
		e_code = 0;
	aux->next->l_c_exit_code = e_code;
}

void	ms_add_history(t_ms *ms, char *line, t_cmd *cmds)
{
	t_history	*aux;

	aux = ms->history;
	ms->history_i++;
	if (!aux)
	{
		aux = (t_history *) ft_calloc(1, sizeof(struct s_history));
		aux->index = ms->history_i;
		aux->line = line;
		aux->next = NULL;
		aux->prev = NULL;
		aux->l_c_exit_code = 0;
	}
	else
		ms_add_history_aux(ms, aux, line, cmds);
}
