/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:55:36 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 13:11:40 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void	ms_add_history_aux(t_ms *ms, t_history	*aux, char *line, t_cmd		*cmds)
// {
// 	t_cmd		*tmp;
// 	int			e_code;
// 	char		*tmp2;
// 	t_history	*last_history;

// 	tmp = cmds;
// 	last_history = ms_last_history(aux);
// 	if (!last_history->line && ms->shell_line)
// 		add_history(ms->shell_line);
// 	else if (last_history->line && ft_strncmp(ms->shell_line, last_history->line, ft_strlen(ms->shell_line)))
// 		add_history(ms->shell_line);
// 	while (aux->next)
// 		aux = aux->next;
// 	aux->next = (t_history *) ft_calloc(1 + 1, sizeof(struct s_history));
// 	aux->next->index = ms->history_i;
// 	if (line != NULL)
// 		aux->next->line = ft_strdup(line);
// 	else
// 	{
// 		tmp2 =  ft_strdup(ms->shell_line);
// 		aux->next->line = ft_printf_to_var("%s\n", tmp2);
// 		ft_free_ptr((void *) &tmp2);
// 	}
// 	aux->next->next = NULL;
// 	aux->next->prev = aux;
// 	tmp = ms_dll_cmd_last(cmds);
// 	if (tmp)
// 		e_code = tmp->exit_code;
// 	else
// 		e_code = 0;
// 	aux->next->l_c_exit_code = e_code;
// }

// void	ms_add_history(t_ms *ms, char *line, t_cmd *cmds)
// {
// 	t_history	*aux;

// 	aux = ms->history;
// 	ms->history_i++;
// 	if (!aux)
// 	{
// 		aux = (t_history *) ft_calloc(1 + 1, sizeof(struct s_history));
// 		aux->index = ms->history_i;
// 		aux->line = ft_strdup(line);
// 		aux->next = NULL;
// 		aux->prev = NULL;
// 		aux->l_c_exit_code = 0;
// 	}
// 	else
// 		ms_add_history_aux(ms, aux, line, cmds);
// }

void	ms_add_history(t_ms *ms, char *line, t_cmd *cmds)
{
	if (cmds)
	{
		
	}
	t_history *head;

	head = ms->history;
	if (head == NULL)
	{
		head = ft_calloc(1, sizeof(t_history));
		head->prev = NULL;
		head->next = NULL;
		head->line = line;
	}
	else 
	{
		head = ms_last_history(ms->history);
		head->next = ft_calloc(1, sizeof(t_history));
		head->next->prev = head;
		head->next->next = NULL;
		head->next->line = line;
	}
}
