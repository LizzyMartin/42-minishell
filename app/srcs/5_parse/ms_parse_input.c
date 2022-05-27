/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:15 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 21:47:06 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**init_current_prompt(t_p *curr_prompt)
{
	char	**input_s_by_space;

	input_s_by_space = NULL;
	input_s_by_space = ft_split(\
	curr_prompt->this_p_line_splited_by_pipe[0], ' ');
	curr_prompt->input_fd = 0;
	curr_prompt->input_path = NULL;
	curr_prompt->has_here_doc = 0;
	curr_prompt->only_here_doc = 0;
	curr_prompt->no_cmd_just_redirect = 0;
	return (input_s_by_space);
}

char	**ms_parse_input(t_p *curr_prompt)
{
	char	**input_s_by_space;

	input_s_by_space = init_current_prompt(curr_prompt);
	if (ft_strnstr(input_s_by_space[0], "<<", 2))
	{
		curr_prompt->has_here_doc = 1;
		curr_prompt->hd_limiter = input_s_by_space[1];
		if (!input_s_by_space[2] || ft_mtx_size((void **) \
			input_s_by_space) == 2)
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
	return (input_s_by_space);
}