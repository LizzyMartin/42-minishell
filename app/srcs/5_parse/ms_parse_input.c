/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:15 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 14:58:18 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**init_current_prompt(t_p *curr_prompt)
{
	char	**input_s_by_space;

	input_s_by_space = \
		ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
	curr_prompt->input_fd = 0;
	curr_prompt->input_path = NULL;
	curr_prompt->has_here_doc = 0;
	curr_prompt->only_here_doc = 0;
	curr_prompt->no_cmd_just_redirect = 0;
	curr_prompt->input_redirected_to_file = 0;
	curr_prompt->only_input_redirected_to_file = 0;
	return (input_s_by_space);
}

char	**ms_parse_input(t_p *curr_prompt)
{
	char	**input_s_by_space;
	char	*tmp;

	input_s_by_space = init_current_prompt(curr_prompt);
	if (input_s_by_space != NULL && ft_strnstr(input_s_by_space[0], "<<", 2))
	{
		curr_prompt->has_here_doc = 1;
		tmp = ft_strdup(input_s_by_space[1]);
		curr_prompt->hd_limiter = tmp;
		if (!input_s_by_space[2] || ft_mtx_size((void **) \
			input_s_by_space) == 2)
			curr_prompt->only_here_doc = 1;
	}
	if (input_s_by_space != NULL && curr_prompt->has_here_doc == 0 && \
	ft_strnstr(input_s_by_space[0], "<", 1))
	{
		curr_prompt->input_redirected_to_file = 1;
		tmp = ft_strdup(input_s_by_space[1]);
		curr_prompt->input_path = tmp;
		curr_prompt->input_fd = open(curr_prompt->input_path, O_RDONLY);
		if (curr_prompt->input_fd == -1)
		{
			ft_pf_error("miniheaven: %s %s", \
			curr_prompt->input_path, E_NOTDIR);
			ft_free_ptr((void *) &tmp);
			ft_mtx_free((void **) input_s_by_space);
			return (NULL);
		}
		if (ft_mtx_size((void **) input_s_by_space) == 2)
				curr_prompt->only_input_redirected_to_file = 1;
		ft_free_ptr((void *) &tmp);
	}
	return (input_s_by_space);
}
