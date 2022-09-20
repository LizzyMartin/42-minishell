/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grupo_capela <grupo_capela@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:15 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/20 03:32:13 by grupo_capel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

// static void	ms_parse_input_aux(t_p *curr_prompt, \
// char **input_s_by_space, char *tmp)
// {


// }

// static char	**reset_split_prompt(t_p *curr_prompt)
// {
// 	char	**input_s_by_space;

// 	return (input_s_by_space);
// }

// static char	*parse_input_aux(char **input_s_by_space)
// {
// 	char	*tmp;

// 	if (!input_s_by_space[1])
// 		tmp = ft_substr(input_s_by_space[0],
// 				ft_str_indexof(input_s_by_space[0], "<",
// 					ft_strlen(input_s_by_space[0])) + 1,
// 				ft_strlen(input_s_by_space[0]));
// 	else
// 		tmp = ft_strdup(input_s_by_space[1]);
// 	tmp = NULL;
// 	return (tmp);
// }


// splited_by_chr
// [0] cat 
// [0] EOF | tr a b

// split_by_space
// EOF 
//  tr 
//  a 
//  b


char	**ms_parse_input(t_p *curr_prompt)
{
	char	**splited_by_chr;
	char 	**split_by_space;
	char	*tmp;
	// char	*divider;
	int		len;

	len = 0;
	// divider = NULL;
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


	if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<<", len))
	{
		curr_prompt->has_here_doc = 1;
		splited_by_chr = \
			ft_split_by_str(curr_prompt->this_p_line_splited_by_pipe[0], "<<");
		split_by_space = ft_split(splited_by_chr[1], ' ');
		tmp = ft_strdup(split_by_space[0]);
		curr_prompt->hd_limiter = ft_strdup(tmp);
		if (ft_strncmp(splited_by_chr[0], " ", ft_strlen(splited_by_chr[0])) == 0)
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
				curr_prompt->this_p_line_splited_by_pipe[0] = ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
				split_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');				
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
					curr_prompt->this_p_line_splited_by_pipe[0] = ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
					split_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');				
					return (split_by_space);
				}
			}
		}
		ft_free_ptr((void *) &tmp);
	}
	else if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<", len))
	{
		curr_prompt->input_redirected_to_file = 1;		
		splited_by_chr = \
			ft_split_by_str(curr_prompt->this_p_line_splited_by_pipe[0], "<");
		split_by_space = ft_split(splited_by_chr[1], ' ');

		// check file
		tmp = ft_strdup(split_by_space[0]);
		curr_prompt->input_path = ft_strdup(tmp);
		
		curr_prompt->input_fd = open(curr_prompt->input_path, O_RDONLY);
		if (curr_prompt->input_fd == -1)
		{
			ft_pf_error("miniheaven: %s %s", curr_prompt->input_path, E_NOTDIR);
			ft_free_ptr((void *) &tmp);
			return (NULL);
		}
		//if (ft_mtx_size((void **) input_s_by_space) <= 2)
		//		curr_prompt->only_input_redirected_to_file = 1;

		// ft_printf("#arquivo existe#\n");
		// exit(0);
		// continue
		if (ft_strncmp(splited_by_chr[0], " ", ft_strlen(splited_by_chr[0])) == 0)
		{
			ft_printf("TEM NADA ANTES %s %s!\n", split_by_space[0], split_by_space[1]);
			if (split_by_space[1] == NULL)
			{
				curr_prompt->only_input_redirected_to_file = 1;
				return (split_by_space);
			}
			else
			{
				ft_free_ptr((void *) &tmp);
				tmp = ft_printf_to_var("< %s", curr_prompt->input_path);
				curr_prompt->this_p_line_splited_by_pipe[0] = ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
				split_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');				
				return (split_by_space);
			}
		}
		else
		{
			ft_printf("TEM ALGO ANTES!\n");
			if (split_by_space[1] != NULL)
			{
				ft_free_ptr((void *) &tmp);
				tmp = ft_printf_to_var("< %s", curr_prompt->input_path);
				curr_prompt->this_p_line_splited_by_pipe[0] = ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
				split_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');				
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
					curr_prompt->this_p_line_splited_by_pipe[0] = ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp, " ");
					split_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');				
					return (split_by_space);
				}
			}
		}
		ft_free_ptr((void *) &tmp);
	}
	else
		split_by_space = ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');

	return (split_by_space);
}




	// if (input_s_by_space != NULL && curr_prompt->has_here_doc == 0 && \
	// ft_strnstr(input_s_by_space[0], "<", 1))
	// {

	// }
	// ft_free_ptr((void *) &tmp);