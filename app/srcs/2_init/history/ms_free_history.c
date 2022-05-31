# include <minishell.h>

void	ms_free_history(t_ms *ms)
{
	t_history *head;

	head = ms->history;
	while (head->next != NULL)
		head = head->next;
	while (head->prev != NULL)
	{
		head = head->prev;
		if (head->next != NULL)
			ft_free_ptr((void *) &head->next);
	}
	if (head != NULL)
		ft_free_ptr((void *) &head);
}
