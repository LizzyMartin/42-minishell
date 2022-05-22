#include	<minishell.h>

void	ms_print_h(t_ms *ms)
{
   	t_h	*h;

	h = ms->p.h;
	ft_printf("#%s#\n", h->line);
}
