/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_parse_commands_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/10 19:55:04 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	prepare_cmd_line(const t_p *curr_prompt, \
	char **input_s_by_space, int c, t_cmd *curr_command)
{
	char	*tmp;
	int		aux;

	tmp = NULL;
	if (0)
	{
		if (curr_prompt->has_here_doc == 1)
		{
			aux = ft_strlen(input_s_by_space[0]) \
				+ ft_strlen(input_s_by_space[1]) + 2;
			tmp = ft_strdup(curr_prompt->this_p_line_splited_by_pipe[c]);
			ft_free_ptr((void *) &curr_command->cmd_line);
			curr_command->cmd_line = ft_substr(tmp + aux, 0, ft_strlen(tmp));
		}
		else if (c == 0 && curr_prompt->input_redirected_to_file == 1)
		{
			aux = ft_strlen(input_s_by_space[0]) \
				+ ft_strlen(input_s_by_space[1]) + 2;
			tmp = ft_strdup(curr_prompt->this_p_line_splited_by_pipe[c]);
			ft_free_ptr((void *) &curr_command->cmd_line);
			curr_command->cmd_line = ft_substr(tmp + aux, 0, ft_strlen(tmp));
		}
	}
	ft_free_ptr((void *) &tmp);
}

char	**get_string(t_p *curr_prompt, char **split_by_space, \
	char *arg, char **str_op)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(curr_prompt->this_p_line_splited_by_pipe[0], \
ft_str_indexof(curr_prompt->this_p_line_splited_by_pipe[0], *str_op, \
ft_strlen(curr_prompt->this_p_line_splited_by_pipe[0])), \
ft_str_indexof(curr_prompt->this_p_line_splited_by_pipe[0], arg, \
ft_strlen(curr_prompt->this_p_line_splited_by_pipe[0])) - 1);
	tmp2 = ft_strtrim(tmp, " ");
	curr_prompt->this_p_line_splited_by_pipe[0] = \
ft_str_replace(curr_prompt->this_p_line_splited_by_pipe[0], tmp2, " ");
	split_by_space = \
ft_split(curr_prompt->this_p_line_splited_by_pipe[0], ' ');
	ft_free_ptr((void *) &tmp);
	ft_free_ptr((void *) &tmp2);
	return (split_by_space);
}
