# include <minishell.h>

void	ms_free_history(t_ms *ms)
{
	t_history	*free;
    t_history   *stack;

    stack = ms->history;
	while (stack != NULL)
	{
		free = stack;
		stack = stack->next;
		ft_free_ptr((void *) &free);
	}
    ms->history = NULL;
}