# include <minishell.h>

void	ms_free_history(t_ms *ms)
{
	t_history	*delete;
    t_history   *stack;

    stack = ms->history;
	while (stack != NULL)
	{
		delete = stack;
		ft_free_ptr((void *) &(delete->line));
		stack = delete->next;
		ft_free_ptr((void *) &delete);
	}
	ft_free_ptr((void *) &delete);
    ms->history = NULL;
}
