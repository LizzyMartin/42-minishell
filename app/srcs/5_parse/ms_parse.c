/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/30 20:38:15 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*typedef struct s_prompt
{
	struct s_prompt			*prev;
	struct s_prompt			*next;
	int						has_here_doc;
	int						only_here_doc;
	int						pipe_here_doc[2];
	char					*hd_limiter;
	int						input_fd;
	char					*input_path;
	int						input_redirected_to_file;
	int						only_input_redirected_to_file;
	int						no_cmd_just_redirect;
	int						pipe[2];
	int						output_fd;
	char					*output_path;
	int						redirect;
	int						pipe_amount;
	t_cmd					*cmds;
	int						aux_fd;
	char					*this_p_line;
	char					**this_p_line_splited_by_pipe;
	int						args_amount;
}	t_p;*/

t_p	*ms_get_prompt(t_ms *ms, t_p *curr_prompt, int i)
{
	if (i >= 1)
	{
		curr_prompt->next = (t_p *) ft_calloc (1, sizeof(t_p));
		curr_prompt->next->prev = curr_prompt;
		curr_prompt = curr_prompt->next;
		curr_prompt->next = NULL;
		
		curr_prompt->has_here_doc = 0;
		curr_prompt->only_here_doc = 0;
		curr_prompt->hd_limiter = NULL;
		curr_prompt->input_fd = 0;
		curr_prompt->input_path = NULL;
		curr_prompt->input_redirected_to_file = 0;
		curr_prompt->only_input_redirected_to_file = 0;
		curr_prompt->no_cmd_just_redirect = 0;
		curr_prompt->output_fd = 1;
		curr_prompt->output_path = NULL;
		curr_prompt->redirect = 0;
		curr_prompt->pipe_amount = 0;
		curr_prompt->cmds = NULL;
		curr_prompt->aux_fd = 0;
		curr_prompt->this_p_line = NULL;
		curr_prompt->this_p_line_splited_by_pipe = NULL;
		curr_prompt->args_amount = 0;
	}
	if (ms->slt_splited_by_connectors)
		curr_prompt->this_p_line = ms->slt_splited_by_connectors[i];
	else
		curr_prompt->this_p_line = ms->shell_line_tokenized;
	curr_prompt->this_p_line_splited_by_pipe = \
		ft_split_by_str(curr_prompt->this_p_line, T_PIPE);
	curr_prompt->args_amount = ft_mtx_size((void **) \
		curr_prompt->this_p_line_splited_by_pipe);
	return (curr_prompt);
}

int	ms_parse(t_ms *ms)
{
	t_p		*curr_prompt;
	int		i;
	char	**input_s_by_space;
	char	**output_s_by_space;

	curr_prompt = NULL;
	input_s_by_space = NULL;
	output_s_by_space = NULL;
	if (ft_strnstr(ms->shell_line_tokenized, \
		T_CONNECTOR, ft_strlen(ms->shell_line_tokenized)))
	{
		ms->slt_splited_by_connectors = \
			ft_split_by_str(ms->shell_line_tokenized, T_CONNECTOR);
		ms->p_amount = ft_mtx_size((void **) ms->slt_splited_by_connectors);
	}
	else
		ms->slt_splited_by_connectors = NULL;
	ms->p = (t_p *) ft_calloc(1, sizeof(t_p));
	ms->p->next = NULL;
	ms->p->prev = NULL;
	
	ms->p->has_here_doc = 0;
	ms->p->only_here_doc = 0;
	ms->p->hd_limiter = NULL;
	ms->p->input_fd = 0;
	ms->p->input_path = NULL;
	ms->p->input_redirected_to_file = 0;
	ms->p->only_input_redirected_to_file = 0;
	ms->p->no_cmd_just_redirect = 0;
	ms->p->output_fd = 1;
	ms->p->output_path = NULL;
	ms->p->redirect = 0;
	ms->p->pipe_amount = 0;
	ms->p->cmds = NULL;
	ms->p->aux_fd = 0;
	ms->p->this_p_line = NULL;
	ms->p->this_p_line_splited_by_pipe = NULL;
	ms->p->args_amount = 0;
	
	curr_prompt = ms->p;
	i = 0;
	while (i < ms->p_amount)
	{
		curr_prompt = ms_get_prompt(ms, curr_prompt, i);
		input_s_by_space = ms_parse_input(curr_prompt);
		output_s_by_space = ms_parse_output(curr_prompt);
		curr_prompt->pipe_amount = 0;
		curr_prompt->pipe_amount = ft_mtx_size((void **) \
			curr_prompt->this_p_line_splited_by_pipe);
		if_there_is_commands_prepare_them_to_be_executed (ms, \
				curr_prompt, output_s_by_space, input_s_by_space);
		ft_mtx_free((void **) curr_prompt->this_p_line_splited_by_pipe);
		ft_mtx_free((void **) input_s_by_space);
		i++;
	}
//	ft_mtx_free((void **) input_s_by_space);
	ft_mtx_free((void **) output_s_by_space);
	return (0);
}

