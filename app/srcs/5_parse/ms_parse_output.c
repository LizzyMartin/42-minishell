/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:19 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/30 22:23:25 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_current_prompt(t_p *curr_prompt, int aux, \
	char *const *output_s_by_space)
{
	if (aux >= 4)
	{
		curr_prompt->output_path = ft_strdup(output_s_by_space[aux - 1]);
		if (ft_strnstr(output_s_by_space[aux - 2], ">>", 2) != NULL)
		{
			curr_prompt->redirect = 1;
			curr_prompt->output_fd = \
				open(curr_prompt->output_path, O_CREAT | \
					O_WRONLY | O_APPEND, 0777);
		}
		else if (ft_strnstr(output_s_by_space[aux - 2], ">", 2) != NULL)
		{
			curr_prompt->redirect = 2;
			curr_prompt->output_fd = \
				open(curr_prompt->output_path, O_CREAT | \
					O_WRONLY | O_TRUNC, 0777);
		}
		if (curr_prompt->redirect > 0)
		{
			if (curr_prompt->output_fd != -1)
				curr_prompt->redirect = 1;
			else
				curr_prompt->redirect = 0;
		}
	}
}

char	**ms_parse_output(t_p *curr_prompt)
{
	int		aux;
	char	**output_s_by_space;
	char	**dup;
	char	*strdup;
	int		mtx_size;

	mtx_size = 0;
	dup = NULL;
	dup = ft_mtx_dup(curr_prompt->this_p_line_splited_by_pipe);
	mtx_size = ft_mtx_size((void **) dup);
	strdup = ft_strdup(curr_prompt->this_p_line_splited_by_pipe[mtx_size - 1]);
	output_s_by_space = ft_split(strdup, ' ');
	aux = ft_mtx_size((void **) output_s_by_space);
	curr_prompt->redirect = 0;
	curr_prompt->output_fd = 1;
	curr_prompt->output_path = NULL;
	update_current_prompt(curr_prompt, aux, output_s_by_space);
	ft_mtx_free((void **) dup);
	return (output_s_by_space);
}
