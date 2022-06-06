/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/06 19:47:22 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	reset_prompt(t_p **curr_prompt)
{
	(*curr_prompt) = (*curr_prompt)->next;
	(*curr_prompt)->next = NULL;
	(*curr_prompt)->has_here_doc = 0;
	(*curr_prompt)->only_here_doc = 0;
	(*curr_prompt)->hd_limiter = NULL;
	(*curr_prompt)->input_fd = 0;
	(*curr_prompt)->input_path = NULL;
	(*curr_prompt)->input_redirected_to_file = 0;
	(*curr_prompt)->only_input_redirected_to_file = 0;
	(*curr_prompt)->no_cmd_just_redirect = 0;
	(*curr_prompt)->output_fd = 1;
	(*curr_prompt)->output_path = NULL;
	(*curr_prompt)->redirect = 0;
	(*curr_prompt)->pipe_amount = 0;
	(*curr_prompt)->cmds = NULL;
	(*curr_prompt)->aux_fd = 0;
	(*curr_prompt)->this_p_line = NULL;
	(*curr_prompt)->this_p_line_splited_by_pipe = NULL;
	(*curr_prompt)->args_amount = 0;
}

t_p	*ms_get_prompt(t_ms *ms, t_p *curr_prompt, int i)
{
	if (i >= 1)
	{
		curr_prompt->next = (t_p *) ft_calloc (1, sizeof(t_p));
		curr_prompt->next->prev = curr_prompt;
		reset_prompt(&curr_prompt);
	}
	if (ms->slt_splited_by_connectors)
		curr_prompt->this_p_line = ms->slt_splited_by_connectors[i];
	else
		curr_prompt->this_p_line = ms->shell_line_tokenized;
	if (ft_strnstr(curr_prompt->this_p_line, T_SPACE, ft_strlen(curr_prompt->this_p_line)) == NULL) {
		curr_prompt->this_p_line_splited_by_pipe = \
            ft_split_by_str(curr_prompt->this_p_line, T_PIPE);
		curr_prompt->args_amount = ft_mtx_size((void **) \
        curr_prompt->this_p_line_splited_by_pipe);
	}
	else
	{
		curr_prompt->this_p_line_splited_by_pipe = \
            ft_split_by_str(ft_str_replace_all(curr_prompt->this_p_line, T_PIPE, "|"), "audklahdakjnfdakjbfak");
		curr_prompt->args_amount = ft_mtx_size((void **) \
        curr_prompt->this_p_line_splited_by_pipe);
	}
	return (curr_prompt);
}

t_p	*parse_prompts(t_ms *ms)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	if (ft_strnstr(ms->shell_line_tokenized, \
		T_CONNECTOR, ft_strlen(ms->shell_line_tokenized)))
	{
		ms->slt_splited_by_connectors = \
			ft_split_by_str(ms->shell_line_tokenized, T_CONNECTOR);
		ms->p_amount = ft_mtx_size((void **) ms->slt_splited_by_connectors);
		ms->connectors_order = ft_calloc ((ms->p_amount) + 1, sizeof(int));
		while (ms->shell_line[i])
		{
			if (ft_strncmp((ms->shell_line + i), "&&", 2) == 0)
				ms->connectors_order[z++] = 1;
			else if (ft_strncmp((ms->shell_line + i), "||", 2) == 0)
				ms->connectors_order[z++] = 2;
			i++;
		}
	}
	else
	{
		ms->slt_splited_by_connectors = NULL;
		ms->connectors_order = NULL;
	}
	ms->p = (t_p *) ft_calloc(1, sizeof(t_p));
	ms->p->next = NULL;
	ms->p->prev = NULL;
	return (ms->p);
}

int	ms_parse(t_ms *ms)
{
	t_p		*curr_prompt;
	int		i;
	char	**input_s_by_space;
	char	**output_s_by_space;

	input_s_by_space = NULL;
	output_s_by_space = NULL;
	curr_prompt = parse_prompts(ms);
	i = 0;
	while (i < ms->p_amount)
	{
		curr_prompt = ms_get_prompt(ms, curr_prompt, i);
		input_s_by_space = ms_parse_input(curr_prompt);
		output_s_by_space = ms_parse_output(curr_prompt);
		curr_prompt->pipe_amount = ft_mtx_size((void **) \
			curr_prompt->this_p_line_splited_by_pipe);
		if (curr_prompt->only_here_doc == 0
		&& curr_prompt->only_input_redirected_to_file == 0)
		{
			ms_parse_commands (ms, curr_prompt, \
			output_s_by_space, input_s_by_space);
		}
		ft_mtx_free((void **) curr_prompt->this_p_line_splited_by_pipe);
		ft_mtx_free((void **) input_s_by_space);
		ft_mtx_free((void **) output_s_by_space);
		i++;
	}
	//ft_mtx_free((void **) input_s_by_space);
	//ft_mtx_free((void **) output_s_by_space);
	return (0);
}
