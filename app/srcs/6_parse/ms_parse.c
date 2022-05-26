#include <minishell.h>

int is_input_command(char *name)
{
	if (ft_strnstr(name, "cat", ft_strlen(name)) || \
	    ft_strnstr(name, "more", ft_strlen(name)) || \
	    ft_strnstr(name, "less", ft_strlen(name)) || \
	    ft_strnstr(name, "tail", ft_strlen(name)) || \
	    ft_strnstr(name, "wc", ft_strlen(name)) || \
	    ft_strnstr(name, "touch", ft_strlen(name))
	   )
		return (1);

	return (0);
}

int	ms_parse(t_ms *ms)
{
	t_p		*curr_prompt;
	int		i;
	int 	aux;
	char 	**input_s_by_space;
	char 	**output_s_by_space;

    input_s_by_space = NULL;
	output_s_by_space = NULL;
	/* 0 - there is connectors ? && or || */
	if (ft_strnstr(ms->shell_line_tokenized, T_CONNECTOR, ft_strlen(ms->shell_line_tokenized)))
	{
		ms->slt_splited_by_connectors = ft_split_by_str(ms->shell_line_tokenized, T_CONNECTOR);
	    ms->p_amount = ft_mtx_size((void ** ) ms->slt_splited_by_connectors);
	}
	else
	{
		ms->slt_splited_by_connectors = NULL;

	}

	curr_prompt = &ms->p;
	i = 0;
	while (i < ms->p_amount)
	{

	// 2 - malloc prompts
		if (i >= 1)
		{
			curr_prompt->next = (t_p *) malloc (sizeof(t_p));
			curr_prompt->next->prev = curr_prompt;
			curr_prompt = curr_prompt->next;
			curr_prompt->next = NULL;
		}
		if (ms->slt_splited_by_connectors)
		     curr_prompt->this_p_line = ms->slt_splited_by_connectors[i];
		else
		     curr_prompt->this_p_line = ms->shell_line_tokenized;

        // split by pipe
		if (ft_strnstr(curr_prompt->this_p_line, T_PIPE, ft_strlen(T_PIPE)) == 0)
		{
			curr_prompt->this_p_line_splited_by_pipe = ft_split_by_str(curr_prompt->this_p_line, T_PIPE);
			curr_prompt->args_amount = ft_mtx_size((void **) curr_prompt->this_p_line_splited_by_pipe);
		}

		/* 1. INPUT */
		input_s_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
		curr_prompt->input_fd = 0;
		curr_prompt->input_path = NULL;
		curr_prompt->has_here_doc = 0;
		curr_prompt->only_here_doc = 0;
		curr_prompt->no_cmd_just_redirect = 0;

		// here doc -> << LIMITER
		if (ft_strnstr(input_s_by_space[0], "<<", 2))
		{
			curr_prompt->has_here_doc = 1;
			curr_prompt->hd_limiter = input_s_by_space[1];
			if (!input_s_by_space[2] || ft_mtx_size((void **) input_s_by_space) == 2)
				curr_prompt->only_here_doc = 1;
		}

		curr_prompt->input_redirected_to_file = 0;
        curr_prompt->only_input_redirected_to_file = 0;
		if (ft_strnstr(input_s_by_space[0], "<", 1))
		{
			curr_prompt->input_redirected_to_file = 1;
			curr_prompt->input_path = ft_strdup(input_s_by_space[1]);
			curr_prompt->input_fd = open(curr_prompt->input_path, O_RDONLY);
		    if (ft_mtx_size((void **) input_s_by_space) == 2)
			     curr_prompt->only_input_redirected_to_file = 1;
		}

		/* 2. OUPUT */
			output_s_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[ft_mtx_size((void **) curr_prompt->this_p_line_splited_by_pipe) - 1], ' ');
			aux = ft_mtx_size((void **) output_s_by_space);
			curr_prompt->redirect = 0;
			curr_prompt->output_fd = 1;
			curr_prompt->output_path = NULL;

			if (aux >= 4)
			{
				curr_prompt->output_path = ft_strdup(output_s_by_space[aux - 1]);
				if (ft_strnstr(output_s_by_space[aux - 2], ">>", 2) != NULL)
				{
					curr_prompt->redirect = 1;
					curr_prompt->output_fd = open(curr_prompt->output_path, O_CREAT | O_WRONLY | O_APPEND, 0777);
				}
				else if (ft_strnstr(output_s_by_space[aux - 2], ">", 2) != NULL)
				{
					curr_prompt->redirect = 2;
					curr_prompt->output_fd = open(curr_prompt->output_path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
				}
				if (curr_prompt->redirect > 0)
				{
					if (curr_prompt->output_fd != -1)
							curr_prompt->redirect = 1;
					else
							curr_prompt->redirect = 0;
				}
			}

		/* 3 - how many commands? | */
		int c;

		c = 0;
		curr_prompt->pipe_amount = 0;
		curr_prompt->pipe_amount = ft_mtx_size((void **) curr_prompt->this_p_line_splited_by_pipe);

		// 3.2 - iterate commands and fill them
		t_cmd *curr_command;

        curr_prompt->cmds = (t_cmd *) malloc (sizeof(t_cmd));
		curr_command = curr_prompt->cmds;
		curr_command->prev = NULL;
		curr_command->next = NULL;
		curr_command->exit_code = 0;
		while (c < curr_prompt->pipe_amount)
		{
			if (c > 0)
			{
		        curr_command->next = (t_cmd *) malloc (sizeof(t_cmd));
		        curr_command->next->prev = curr_command;
		        curr_command = curr_command->next;
		        curr_command->next = NULL;
			}
			curr_command->exit_code = 0;
			curr_command->index = c;
			curr_command->cmd_line = curr_prompt->this_p_line_splited_by_pipe[c];

			if (curr_prompt->has_here_doc == 1)
			{
				aux = ft_strlen(input_s_by_space[0]) + ft_strlen(input_s_by_space[1]) + 2;
				char *tmp = curr_prompt->this_p_line_splited_by_pipe[c] + aux;
				curr_command->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp));
			}

			 if (c == 0 && curr_prompt->input_redirected_to_file == 1)
			{
				aux = ft_strlen(input_s_by_space[0]) + ft_strlen(input_s_by_space[1]) + 2;
				char *tmp = curr_prompt->this_p_line_splited_by_pipe[c] + aux;
				curr_command->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp));
			}


			if (c == (curr_prompt->pipe_amount - 1) && curr_prompt->redirect > 0)
			{
				int length = ft_mtx_size((void **) output_s_by_space);
				aux = ft_strlen(output_s_by_space[length - 2]) + ft_strlen(output_s_by_space[length - 1]) + 1;
				char *tmp;
				if (curr_prompt->has_here_doc == 0)
					tmp = curr_prompt->this_p_line_splited_by_pipe[c];
				else
					tmp = curr_command->cmd_line;
				curr_command->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp) - aux - 1);
				if (ft_strnstr(curr_command->cmd_line, ">>", ft_strlen(curr_command->cmd_line)))
					curr_prompt->no_cmd_just_redirect = 1;
			}

			curr_command->cmd_splited_by_space = ft_split(curr_command->cmd_line, ' ');
			curr_command->args_amount = ft_mtx_size((void **) curr_command->cmd_splited_by_space);
			curr_command->just_name = curr_command->cmd_splited_by_space[0];
			curr_command->path_and_name = append_path(curr_command, ms);

			/* INPUT */
			if (is_input_command(curr_command->just_name) == 1)
			{
				// {
				// 	curr_prompt->input_fd = 0;
				// 	curr_prompt->input_path = NULL;
				// }
				// else
				if (curr_command->args_amount >= 2 && curr_command->index == 0)
				{
					curr_prompt->input_path = ft_strdup(curr_command->cmd_splited_by_space[1]);
					curr_prompt->input_fd = open(curr_command->cmd_splited_by_space[1], O_RDONLY);
				}
				//ft_printf("#%d#", curr_command->args_amount);
			}
        c++;
		}
		i++;
	}
	return (0);
}
