# include <minishell.h>

void	ms_free_prompt(t_p *curr_prompt)
{
	t_p *tmp;

	while (curr_prompt)
	{
         tmp = curr_prompt;
         ms_dll_cmd_free(tmp->cmds);
		 //ft_mtx_free((void **) tmp->this_p_line_splited_by_pipe);
		 //ft_mtx_free((void *) &tmp->this_p_line);
         curr_prompt = curr_prompt->next;
		 ft_free_ptr((void *) &tmp);
	}	
}