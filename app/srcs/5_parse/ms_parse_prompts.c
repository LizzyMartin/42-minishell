/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_prompts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:39:53 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/03 21:09:21 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	reset_prompt(t_p **curr_prompt)
{
	(*curr_prompt) = (*curr_prompt)->next;
	(*curr_prompt)->next = NULL;
	(*curr_prompt)->has_here_doc = 0;
	(*curr_prompt)->only_here_doc = 0;
	(*curr_prompt)->hd_limiter = NULL;
	(*curr_prompt)->input_fd = -1;
	(*curr_prompt)->input_path = NULL;
	(*curr_prompt)->input_redirected_to_file = 0;
	(*curr_prompt)->only_input_redirected_to_file = 0;
	(*curr_prompt)->only_redirect_to_file = 0;
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

static void	ms_get_prompt_2(t_p *curr_prompt)
{
	ft_mtx_free((void **) curr_prompt->this_p_line_splited_by_pipe);
	curr_prompt->this_p_line_splited_by_pipe = \
	ft_split_by_str(curr_prompt->this_p_line, T_PIPE);
	curr_prompt->args_amount = ft_mtx_size((void **) \
	curr_prompt->this_p_line_splited_by_pipe);
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
		curr_prompt->this_p_line = ft_strdup(ms->slt_splited_by_connectors[i]);
	else
		curr_prompt->this_p_line = ft_strdup(ms->shell_line_tokenized);
	ms_get_prompt_2(curr_prompt);
	return (curr_prompt);
}

static void	ms_connectors_order(t_ms *ms)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
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

t_p	*parse_prompts(t_ms *ms)
{
	if (ft_strnstr(ms->shell_line_tokenized, \
		T_CONNECTOR, ft_strlen(ms->shell_line_tokenized)))
	{
		ms->slt_splited_by_connectors = \
			ft_split_by_str(ms->shell_line_tokenized, T_CONNECTOR);
		ms->p_amount = ft_mtx_size((void **) ms->slt_splited_by_connectors);
		ms_connectors_order(ms);
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
