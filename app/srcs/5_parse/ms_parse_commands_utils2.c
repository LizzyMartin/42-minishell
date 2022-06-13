/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_commands_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 19:46:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_parse_commands2(t_ms *ms, const t_p *curr_prompt, \
int c, t_cmd *curr_command)
{
	curr_command->exit_code = 0;
	curr_command->index = c;
	ft_free_ptr((void *) &ms->tmp2);
	ms->tmp2 = ft_strdup(curr_prompt->this_p_line_splited_by_pipe[c]);
	curr_command->cmd_line = ft_strdup(ms->tmp2);
}
