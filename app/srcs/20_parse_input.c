/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:15 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/16 20:49:38 by acapela-         ###   ########.fr       */
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

cat | EOF tr a b



// cat << EOF | tr a b

char	**ms_parse_input(t_p *curr_prompt)
{
	char	**input_s_by_space;
	char	*tmp;
	char	*divider;
	int		len;
	char 	**split2;

	// set to null
	len = 0;
	divider = NULL;
	tmp = NULL;
	input_s_by_space = NULL;
	curr_prompt->input_fd = 0;
	curr_prompt->input_path = NULL;
	curr_prompt->has_here_doc = 0;
	curr_prompt->only_here_doc = 0;
	curr_prompt->no_cmd_just_redirect = 0;
	curr_prompt->input_redirected_to_file = 0;
	curr_prompt->only_input_redirected_to_file = 0;
	len = ft_strlen(curr_prompt->this_p_line_splited_by_pipe[0]);

	// identify if have <<
	if (ft_strnstr(curr_prompt->this_p_line_splited_by_pipe[0], "<<", len))
	{
		curr_prompt->has_here_doc = 1;
		input_s_by_space = \
			ft_split_by_str(curr_prompt->this_p_line_splited_by_pipe[0], "<<");
		split2 = ft_split(input_s_by_space[1], ' ');
		tmp = ft_strdup(split2[0]);
		curr_prompt->hd_limiter = ft_strdup(tmp);
		if (input_s_by_space[0][0] == ' ')
		{
			if (split2[1] == NULL)
				curr_prompt->only_here_doc = 1;
			else
				// get after delimiter;
		}
		else if (input_s_by_space[0][0] != ' ')
		{
			// get before here_doc

		}
		ft_free_ptr((void *) &tmp);
	}

	// if (input_s_by_space != NULL && curr_prompt->has_here_doc == 0 && \
	// ft_strnstr(input_s_by_space[0], "<", 1))
	// {
	// 	curr_prompt->input_redirected_to_file = 1;
	// 	tmp = parse_input_aux(input_s_by_space);
	// 	curr_prompt->input_path = tmp;
	// 	curr_prompt->input_fd = open(curr_prompt->input_path, O_RDONLY);
	// 	if (curr_prompt->input_fd == -1)
	// 	{
	// 		ft_pf_error("miniheaven: %s %s", curr_prompt->input_path, E_NOTDIR);
	// 		ft_free_ptr((void *) &tmp);
	// 		ft_mtx_free((void **) input_s_by_space);
	// 		return (NULL);
	// 	}
	// 	if (ft_mtx_size((void **) input_s_by_space) <= 2)
	// 			curr_prompt->only_input_redirected_to_file = 1;
	// }
	// ft_free_ptr((void *) &tmp);

	return (input_s_by_space);
}
