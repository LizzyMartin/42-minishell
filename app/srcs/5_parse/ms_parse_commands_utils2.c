/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_commands_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/14 17:19:12 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	prepare_cmd_line(const t_p *curr_prompt, \
	char **input_s_by_space, int c, t_cmd *curr_command)
{
	char	*tmp;
	int		aux;

	tmp = NULL;
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
	ft_free_ptr((void *) &tmp);
}
