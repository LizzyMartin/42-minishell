/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:15 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/27 22:52:58 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static char	**here_doc_input_file(int op, t_p *curr_prompt)
{
	char	*str_op;
	char	**splited_by_chr;
	char	**split_by_space;
	char	*tmp;
	int		len;

	if (op == 1)
	{
		str_op = ft_strdup("<<");
		curr_prompt->has_here_doc = 1;
	}
	else
	{
		str_op = ft_strdup("<");
		curr_prompt->input_redirected_to_file = 1;
	}
	len = 0;
	tmp = NULL;
	splited_by_chr = NULL;
	split_by_space = NULL;
	char	*arg;
	len = ft_strlen(curr_prompt->this_p_line_splited_by_pipe[0]);
		splited_by_chr = \
			ft_split_by_str(curr_prompt->this_p_line_splited_by_pipe[0], str_op);
		split_by_space = ft_split(splited_by_chr[1], ' ');
		tmp = ft_strdup(split_by_space[0]);
		if (op == 1)
		{
			curr_prompt->hd_limiter = ft_strdup(tmp);
			arg = curr_prompt->hd_limiter;
		}
		else
		{
			curr_prompt->input_path = ft_strdup(tmp);
			arg = curr_prompt->input_path;
			curr_prompt->input_fd = open(curr_prompt->input_path, O_RDONLY);
			if (curr_prompt->input_fd == -1)
			{
				ft_pf_error("miniheaven: %s %s", curr_prompt->input_path, E_NOTDIR);
				ft_free_ptr((void *) &tmp);
				return (NULL);
			}
		}
		if (ft_strncmp(splited_by_chr[0], \
" ", ft_strlen(splited_by_chr[0])) == 0)  // nada antes
		{
			if (split_by_space[1] == NULL) // << EOF
			{
				// ft_printf("A\n");
				if (op == 1)
					curr_prompt->only_here_doc = 1;
				else if(op == 2)
					curr_prompt->only_input_redirected_to_file = 1;
				return (split_by_space);
			}
			else // << EOF tr a b
			{
				// ft_printf("B\n");
				int i = 0;
				char *tmp = ft_strdup(curr_prompt->this_p_line_splited_by_pipe[0]);
				i += ft_str_indexof(tmp, arg, ft_strlen(tmp)) + ft_strlen(arg);
				tmp = ft_substr(tmp, i, ft_strlen(tmp));
				curr_prompt->this_p_line_splited_by_pipe[0] = tmp;
				split_by_space = ft_split(tmp, ' ');
				// ft_printf("#%d %s#\n", i, tmp);
				return (split_by_space);
				
			}
		}
		else // algo antes
		{
			if (split_by_space[1] != NULL) // cat << EOF tr a b
			{
				ft_printf("C\n");
				ft_free_ptr((void *) &tmp);
				tmp = ft_printf_to_var("%s %s",str_op, arg);
				curr_prompt->this_p_line_splited_by_pipe[0] = \
ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
				split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
				return (split_by_space);
			}
			else // cat << EOF
			{
				int n = ft_mtx_size((void **) curr_prompt->this_p_line_splited_by_pipe);
				ft_printf("D (%d)\n", n);
				if (n <= 1)
				{
					// ft_printf("D 1\n");
					if (op == 1)
						curr_prompt->only_here_doc = 2;
					else if (op == 2)
						curr_prompt->only_input_redirected_to_file = 2;
					return (split_by_space);
				}
				else
				{
					curr_prompt->dont_execute_first = 1;
					return (split_by_space);
				}
			}
		}
		ft_free_ptr((void *) &tmp);
}

char	**ms_parse_input(t_p *curr_prompt)
{
	int		len;

	len = 0;
	len = ft_strlen(curr_prompt->this_p_line_splited_by_pipe[0]);
	curr_prompt->input_fd = 0;
	curr_prompt->input_path = NULL;
	curr_prompt->has_here_doc = 0;
	curr_prompt->only_here_doc = 0;
	curr_prompt->no_cmd_just_redirect = 0;
	curr_prompt->input_redirected_to_file = 0;
	curr_prompt->only_input_redirected_to_file = 0;
	if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<<", len))
		return (here_doc_input_file(1, curr_prompt));
	else if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<", len))
		return (here_doc_input_file(2, curr_prompt));
	else
		return (ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' '));
}

		
// 	{
// 		curr_prompt->input_redirected_to_file = 1;
// 		splited_by_chr = \
// 			ft_split_by_str(curr_prompt->this_p_line_splited_by_pipe[0], "<");
// 		split_by_space = ft_split(splited_by_chr[1], ' ');
// 		tmp = ft_strdup(split_by_space[0]);
// 		curr_prompt->input_path = ft_strdup(tmp);
// 		curr_prompt->input_fd = open(curr_prompt->input_path, O_RDONLY);
// 		if (curr_prompt->input_fd == -1)
// 		{
// 			ft_pf_error("miniheaven: %s %s", curr_prompt->input_path, E_NOTDIR);
// 			ft_free_ptr((void *) &tmp);
// 			return (NULL);
// 		}
// 		if (ft_strncmp(splited_by_chr[0], \
// " ", ft_strlen(splited_by_chr[0])) == 0)
// 		{
// 			if (split_by_space[1] == NULL)
// 			{
// 				curr_prompt->only_input_redirected_to_file = 1;
// 				return (split_by_space);
// 			}
// 			else
// 			{
// 				ft_free_ptr((void *) &tmp);
// 				tmp = ft_printf_to_var("< %s", curr_prompt->input_path);
// 				curr_prompt->this_p_line_splited_by_pipe[0] = \
// ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
// 				split_by_space = \
// ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
// 				return (split_by_space);
// 			}
// 		}
// 		else
// 		{
// 			if (split_by_space[1] != NULL)
// 			{
// 				ft_free_ptr((void *) &tmp);
// 				tmp = ft_printf_to_var("< %s", curr_prompt->input_path);
// 				curr_prompt->this_p_line_splited_by_pipe[0] = \
// ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
// 				split_by_space = \
// ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
// 				return (split_by_space);
// 			}
// 			else
// 			{
// 				if (is_input_command(ft_strtrim(splited_by_chr[0], " ")))
// 					curr_prompt->only_input_redirected_to_file = 2;
// 				else
// 				{
// 					ft_free_ptr((void *) &tmp);
// 					tmp = ft_printf_to_var("< %s", curr_prompt->input_path);
// 					curr_prompt->this_p_line_splited_by_pipe[0] = \
// ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
// 					split_by_space = \
// ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
// 					return (split_by_space);
// 				}
// 			}
// 		}
// 		ft_free_ptr((void *) &tmp);