#include    <minishell.h>

void    ms_add_history(t_ms *ms, char *line, t_cmd *cmds)
{
    t_history   *aux;
	t_cmd		*tmp;

	tmp = cmds;
    aux = ms->history;
	ms->history_i++;
	if (!aux)
	{
		aux = (t_history *) malloc(sizeof(struct s_history));
		aux->index = ms->history_i;
		aux->line = line;
		aux->next = NULL;
		aux->prev = NULL;
		aux->l_c_exit_code = 0;
	}
	else
	{
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = (t_history *) malloc(sizeof(struct s_history));
		aux->next->index = ms->history_i;
		if (line != NULL)
			aux->next->line = line;
		else
			aux->next->line = ft_printf_to_var("%s\n", ms->shell_line);
		aux->next->next = NULL;
		aux->next->prev = aux;
		tmp = ms_dll_cmd_last(cmds);
		int e_code;
		if (tmp)
			e_code = tmp->exit_code;
		else
			e_code = 0;
		aux->next->l_c_exit_code = e_code;
	}
}
