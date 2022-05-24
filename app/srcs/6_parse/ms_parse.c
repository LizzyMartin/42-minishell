#include <minishell.h>

int is_input_command(char *name)
{
	if (ft_strnstr(name, "echo", ft_strlen(name)) || \
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
	char 	**input_s_by_space;

    input_s_by_space = NULL;
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
		curr_prompt->this_p_line_splited_by_pipe = ft_split_by_str(curr_prompt->this_p_line, T_PIPE);
		curr_prompt->args_amount = ft_mtx_size((void **) curr_prompt->this_p_line_splited_by_pipe);

		// /* 1 - get input */
		input_s_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
		curr_prompt->input_fd = 0;
		curr_prompt->input_path = NULL;

		// // 1.1 there is here doc ? << LIMITER
		if (ft_strnstr(input_s_by_space[0], "<<", 2))
		{
			curr_prompt->has_here_doc = 1;
			curr_prompt->hd_limiter = input_s_by_space[1];
		}
		else if (is_input_command(input_s_by_space[0]))
		{
	    /* 1.2 the command needs a input ? yes or no! no go on to pipex; 
		yes there is a valid file name ? file.txt */
		    curr_prompt->input_path = ft_strdup(input_s_by_space[1]);
		    curr_prompt->input_fd = open(input_s_by_space[1], O_RDONLY);
		}
		else 
		{
		// the command dont need input
		}

		// /* 2 - set output fd: */
		// //s_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[curr_prompt->args_amount - 1], ' ');

		// curr_prompt->redirect = 0;
		// curr_prompt->output_fd = 1;
        
		// // if (ft_strnstr(s_by_space[0], ">>", 2))
		// // {
		// // 	ft_printf("tem redirect");
		// // 	curr_prompt->output_path = ft_strdup(s_by_space[1]);
		// //     curr_prompt->output_fd = open(curr_prompt->output_path, O_RDONLY);
		// // 	if (curr_prompt->output_fd != -1)
		// // 	     curr_prompt->redirect = 1;
		// //     else
		// // 	     curr_prompt->redirect = 0;
		// // }

		/* 3 - how many commands? | */
		int c;

		c = 0;
		curr_prompt->pipe_amount = 0;
		curr_prompt->pipe_amount = ft_mtx_size((void **) curr_prompt->this_p_line_splited_by_pipe);

		// 3.2 - iterate commands and fill them
		if (curr_prompt->has_here_doc == 1 && ft_mtx_size((void **) input_s_by_space) <= 1)
		{
           curr_prompt->cmds = NULL;
		   i++;
		   continue;
		}
		t_cmd *curr_command;

        curr_prompt->cmds = (t_cmd *) malloc (sizeof(t_cmd));
		curr_command = curr_prompt->cmds;
		curr_command->prev = NULL;
		curr_command->next = NULL;
		while (c < curr_prompt->pipe_amount)
		{
			if (c > 0)
			{	
		        curr_command->next = (t_cmd *) malloc (sizeof(t_cmd));
		        curr_command->next->prev = curr_command;
		        curr_command = curr_command->next;
		        curr_command->next = NULL;
			}
			curr_command->index = c;
		    curr_command->cmd_line = curr_prompt->this_p_line_splited_by_pipe[c];			
			curr_command->cmd_splited_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[c], ' ');
			curr_command->args_amount = ft_mtx_size((void **) curr_command->cmd_splited_by_space);
			curr_command->just_name = curr_command->cmd_splited_by_space[0];
			curr_command->path_and_name = append_path(curr_command, ms);
			//ft_printf("%s %s %s %s\n", curr_command->just_name, curr_command->path_and_name, curr_command->cmd_line, curr_command->cmd_splited_by_space[0]);
            c++;
		}
		i++;
	}
	
	return (0);
}

	// ms->p.cmds = (t_cmd *) malloc(sizeof(t_cmd));
	// ms->p.cmds->name = ms->p.line_splited[0];
	// ms->p.cmds->index = 0;
	// ms->p.cmds->next = NULL;
	// ms->p.cmds->prev = NULL;
	// ms->p.cmds_size = ft_mtx_size((void **) ms->p.line_splited);
	// ms->p.cmds->cmd_splited = NULL;
	// ms->p.cmds->std_in = open(ms->p.line_splited[1], O_RDONLY);
	// ms->p.cmds_size = 1;
	// ms->p.cmds->name_and_path = append_path(ms->p.cmds, ms);

	/*echo "argel"
argel
"argel"

tr a " "

echo argel && ls || echo argel



echo argel |
 tr ab |
  grep a >> teste.txt*/

//cat file.txt | tr a b | grep a >> file2.txt
//cat file.txt | tr a b | grep a >> file2.txt && cat file2.txt

//<< FIM | tr a b | grep a >> file2.txt
/*
	- s_connectors: &&, ||;
	- s_here_doc/s_input: file or << EOF;
	- s_output: >>;
	- s_pipe: |;

*/