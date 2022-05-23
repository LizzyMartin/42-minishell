#include <minishell.h>

void	ms_print_history(t_ms *ms)
{
	t_history 	*h;
	int			i;

	i = 1;
	h = ms->p.history;
	while (h)
	{
		if (h->index != 0 && h->line != NULL)
			ft_printf("  %d  %s", i, h->line);
		i++;
		h = h->next;
	}
}
