/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:24 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/08 15:50:48 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	ms_parse(t_ms *ms)
{
	t_p		*curr_prompt;
	int		i;
	char	**input_s;
	char	**output_s;

	curr_prompt = parse_prompts(ms);
	i = -1;
	while (++i < ms->p_amount)
	{
		curr_prompt = ms_get_prompt(ms, curr_prompt, i);
		input_s = ms_parse_input(curr_prompt);
		if (input_s == NULL)
			return (1);
		output_s = ms_parse_output(curr_prompt);
		curr_prompt->pipe_amount = ft_mtx_size((void **) \
curr_prompt->this_p_line_splited_by_pipe);
		if (curr_prompt->only_here_doc == 0 && \
curr_prompt->only_input_redirected_to_file == 0)
			ms_parse_commands (ms, curr_prompt, output_s, input_s);
		if (!curr_prompt->has_here_doc \
	&& !curr_prompt->input_redirected_to_file)
			ft_mtx_free((void **) input_s);
		ft_mtx_free((void **) output_s);
	}
	return (0);
}
