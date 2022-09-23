/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:15 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/23 22:27:08 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

char	**ms_parse_input(t_p *curr_prompt)
{
	char	**splited_by_chr;
	char	**split_by_space;
	char	*tmp;
	int		len;

	len = 0;
	tmp = NULL;
	splited_by_chr = NULL;
	split_by_space = NULL;
	curr_prompt->input_fd = 0;
	curr_prompt->input_path = NULL;
	curr_prompt->has_here_doc = 0;
	curr_prompt->only_here_doc = 0;
	curr_prompt->no_cmd_just_redirect = 0;
	curr_prompt->input_redirected_to_file = 0;
	curr_prompt->only_input_redirected_to_file = 0;
	len = ft_strlen(curr_prompt->this_p_line_splited_by_pipe[0]);
	// <<
	if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<<", len))
	{
		curr_prompt->has_here_doc = 1;
		splited_by_chr = \
			ft_split_by_str(curr_prompt->this_p_line_splited_by_pipe[0], "<<");
		split_by_space = ft_split(splited_by_chr[1], ' ');
		tmp = ft_strdup(split_by_space[0]);
		curr_prompt->hd_limiter = ft_strdup(tmp);
		if (ft_strncmp(splited_by_chr[0], " ", \
ft_strlen(splited_by_chr[0])) == 0)
		{
			if (split_by_space[1] == NULL)
			{
				curr_prompt->only_here_doc = 1;
				return (split_by_space);
			}
		}
		else
		{
			if (split_by_space[1] != NULL)
			{
				ft_free_ptr((void *) &tmp);
				tmp = ft_printf_to_var("<< %s", curr_prompt->hd_limiter);
				curr_prompt->this_p_line_splited_by_pipe[0] = \
ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
				split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
				return (split_by_space);
			}
			else
			{
				if (is_input_command(ft_strtrim(splited_by_chr[0], " ")))
					curr_prompt->only_here_doc = 2;
				else
				{
					ft_free_ptr((void *) &tmp);
					tmp = ft_printf_to_var("<< %s", curr_prompt->hd_limiter);
					curr_prompt->this_p_line_splited_by_pipe[0] = \
ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
					split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
					return (split_by_space);
				}
			}
		}
		ft_free_ptr((void *) &tmp);
		return (split_by_space);
	}	


	// <
	if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<", len))
	{
		curr_prompt->input_redirected_to_file = 1;
		splited_by_chr = \
			ft_split_by_str(curr_prompt->this_p_line_splited_by_pipe[0], "<");
		split_by_space = ft_split(splited_by_chr[1], ' ');
		tmp = ft_strdup(split_by_space[0]);
		curr_prompt->input_path = ft_strdup(tmp);
		curr_prompt->input_fd = open(curr_prompt->input_path, O_RDONLY);
		if (curr_prompt->input_fd == -1)
		{
			ft_pf_error("miniheaven: %s %s", curr_prompt->input_path, E_NOTDIR);
			ft_free_ptr((void *) &tmp);
			return (NULL);
		}
		if (ft_strncmp(splited_by_chr[0], \
" ", ft_strlen(splited_by_chr[0])) == 0)
		{
			if (split_by_space[1] == NULL)
			{
				curr_prompt->only_input_redirected_to_file = 1;
				return (split_by_space);
			}
			else
			{
				ft_free_ptr((void *) &tmp);
				tmp = ft_printf_to_var("< %s", curr_prompt->input_path);
				curr_prompt->this_p_line_splited_by_pipe[0] = \
ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
				split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
				return (split_by_space);
			}
		}
		else
		{
			if (split_by_space[1] != NULL)
			{
				ft_free_ptr((void *) &tmp);
				tmp = ft_printf_to_var("< %s", curr_prompt->input_path);
				curr_prompt->this_p_line_splited_by_pipe[0] = \
ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
				split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
				return (split_by_space);
			}
			else
			{
				if (is_input_command(ft_strtrim(splited_by_chr[0], " ")))
					curr_prompt->only_input_redirected_to_file = 2;
				else
				{
					ft_free_ptr((void *) &tmp);
					tmp = ft_printf_to_var("< %s", curr_prompt->input_path);
					curr_prompt->this_p_line_splited_by_pipe[0] = \
ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
					split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
					return (split_by_space);
				}
			}
		}
		ft_free_ptr((void *) &tmp);
	return (split_by_space);
	}
	split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
	return (split_by_space);
}
