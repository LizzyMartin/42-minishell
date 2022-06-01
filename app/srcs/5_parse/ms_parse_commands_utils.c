/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/01 00:00:20 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*update_cmd(t_cmd *curr_command)
{
	curr_command->next = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	curr_command->next->prev = curr_command;
	curr_command = curr_command->next;
	curr_command->next = NULL;
	curr_command->can_execute = 1;
	curr_command->error_msg = NULL;
	curr_command->just_name = NULL;
	curr_command->path_and_name = NULL;
	curr_command->cmd_line = NULL;
	curr_command->cmd_splited_by_space = NULL;
	return (curr_command);
}

void	reset_cmd(t_cmd **curr_command)
{
	(*curr_command)->prev = NULL;
	(*curr_command)->next = NULL;
	(*curr_command)->exit_code = 0;
	(*curr_command)->error_msg = NULL;
	(*curr_command)->just_name = NULL;
	(*curr_command)->path_and_name = NULL;
	(*curr_command)->cmd_line = NULL;
	(*curr_command)->cmd_splited_by_space = NULL;
	(*curr_command)->can_execute = 1;
}
