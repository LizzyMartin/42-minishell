# include <minishell.h>

void	ms_free_prompt(t_ms *ms)
{
	t_p		*free;
    t_p		*stack;

    stack = ms->p;
	while (stack != NULL)
	{
		free = stack;
		ft_free_ptr((void *) &free->hd_limiter);
		ft_free_ptr((void *) &free->input_path);
		ft_free_ptr((void *) &free->output_path);
		ft_free_ptr((void *) &free->this_p_line);
		ft_mtx_free((void **) free->this_p_line_splited_by_pipe);
		ms_dll_cmd_free(free->cmds);
		stack = stack->next;
		ft_free_ptr((void *) &free);
	}
    ms->p = NULL;
}