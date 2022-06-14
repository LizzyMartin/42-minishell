/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/14 17:41:46 by acapela-         ###   ########.fr       */
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
	curr_command->exit_code = 0;
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

char	*get_just_name(char *path)
{
	int	i;

	i = ft_strlen(path);
	while (i > 0)
	{
		if (path[i] == '/')
			break ;
		i--;
	}
	return (ft_substr(path, i + 1, ft_strlen(path)));
}

int	is_input_command(char *name)
{
	if (ft_strnstr(name, "cat", ft_strlen(name)) || \
		ft_strnstr(name, "more", ft_strlen(name)) || \
		ft_strnstr(name, "less", ft_strlen(name)) || \
		ft_strnstr(name, "tail", ft_strlen(name)) || \
		ft_strnstr(name, "wc", ft_strlen(name)) || \
		ft_strnstr(name, "touch", ft_strlen(name))
	)
	{
		g_ms->input_command_open = 1;
		return (1);
	}
	return (0);
}

int	is_input_command_alone(t_ms *ms, char *cmd_line)
{
	char	**split;

	ms->input_command_open = 1;
	split = ft_split(cmd_line, ' ');
	if (is_input_command(split[0])
		&& ft_mtx_size((void **) split) == 1)
	{
		ft_mtx_free((void **) split);
		return (1);
	}
	ft_mtx_free((void **) split);
	return (0);
}
