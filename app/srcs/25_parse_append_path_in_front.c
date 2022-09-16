/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_parse_append_path_in_front.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relizabe <relizabe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:44:09 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/15 19:44:21 by relizabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

char	*check_path(int i, t_cmd *current_cmd, char **path)
{
	char	*path_plus_command;

	path_plus_command = ft_printf_to_var("%s/%s",
			path[i], current_cmd->just_name);
	if (access(path_plus_command, X_OK) == 0)
	{
		ft_mtx_free((void **) path);
		current_cmd->can_execute = 1;
		return (path_plus_command);
	}
	ft_free_ptr((void *) &path_plus_command);
	return (NULL);
}

int	check_envpath(char *env_path, t_ms *ms,
		t_cmd *current_cmd, char ***path)
{
	if (env_path == NULL)
	{
		ft_pf_error("miniheaven: %s %s", \
				current_cmd->just_name, E_NOTDIR);
		ms->no_path = 1;
		return (1);
	}
	else
		ms->no_path = 0;
	(*path) = ft_split(env_path, ':');
	return (0);
}

char	*ms_append_path_in_front(t_cmd *current_cmd, t_ms *ms)
{
	char	**path;
	char	*env_path;
	int		i;
	char	*result;

	if (is_builtin(current_cmd->just_name))
	{
		ms->no_path = 0;
		return (NULL);
	}
	i = -1;
	env_path = ms_find_env_value(ms, "PATH");
	if (check_envpath(env_path, ms, current_cmd, &path))
		return (NULL);
	while (path[++i])
	{
		result = check_path(i, current_cmd, path);
		if (result != NULL)
			return (result);
	}
	current_cmd->error_msg = ft_printf_to_var("%s", E_CMDNOTFOUND);
	current_cmd->exit_code = 127;
	current_cmd->can_execute = 0;
	update_exit_code_last_cmd(ms, NULL, 127);
	ft_mtx_free((void **) path);
	return (NULL);
}
