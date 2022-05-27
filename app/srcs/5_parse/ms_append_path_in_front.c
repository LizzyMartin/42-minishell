/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_append_path_in_front.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:09 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 07:30:48 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ms_append_path_in_front(t_cmd *current_cmd, t_ms *ms)
{
	char	**path;
	char	*path_plus_command;
	int		i;

	i = -1;
	while (*(ms->envp))
		if (ft_strnstr(*(ms->envp), "PATH=", sizeof(*(ms->envp))))
			break ;
	else
			ms->envp++;
	path = ft_split(*(ms->envp), ':');
	while (path[++i])
	{
		path_plus_command = ft_printf_to_var("%s/%s",
				path[i], current_cmd->just_name);
		if (access(path_plus_command, X_OK) == 0)
		{
			current_cmd->can_execute = 1;
			return (path_plus_command);
		}
	}
	current_cmd->error_msg = E_CMDNOTFOUND;
	current_cmd->exit_code = 127;
	current_cmd->can_execute = 0;
	return (NULL);
}
