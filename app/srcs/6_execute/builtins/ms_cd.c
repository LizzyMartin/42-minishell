/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:07 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 19:36:39 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_env_value(t_ms *ms, char *key, char *value)
{
	t_env	*env;

	env = ms->envs;
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(env->key)) == 0) && \
			(env->key != NULL && env->value != NULL))
			env->value = value;
		env = env->next;
	}
}

static void	update_env_values(t_ms *ms, t_cmd *current_cmd, \
	char *pwd, char *const *cmd, int aux)
{
	char		*oldpwd;
	char		*line;

	oldpwd = ms_find_env_value(ms, "PWD");
	if (oldpwd)
	{
		if (chdir(cmd[1]) == -1)
		{
			line = ft_printf_to_var("cd: %s: No such file or directory\n", cmd[1]);
			ft_putstr_fd(line, aux);
			current_cmd->exit_code = 1;
		}
		else
		{
			getcwd(pwd, 999);
			update_env_value(ms, "OLDPWD", oldpwd);
			update_env_value(ms, "PWD", pwd);
		}
	}
}

void	ms_cd(t_ms *ms, t_cmd *current_cmd, t_p *prompt)
{
	char		pwd[999];
	char		**cmd;
	char		*line;
	int			aux;
	int			tmp_fd[2];

	pipe(tmp_fd);
	prompt->input_fd = tmp_fd[0];
	aux = tmp_fd[1];
	cmd = current_cmd->cmd_splited_by_space;
	if (current_cmd->index == prompt->args_amount - 1)
		aux = 1;
	current_cmd->exit_code = 0;
	if (!ms_is_in_env(ms, "OLDPWD"))
		ms_add_env(ms, "OLDPWD", ms_find_env_value(ms, "HOME"));
	if (!cmd[1] || !ft_strncmp(cmd[1], "~", ft_strlen(cmd[1]))
		|| !ft_strncmp(cmd[1], "--", 2))
		chdir(getenv("HOME"));
	else if (!ft_strncmp(cmd[1], "-", ft_strlen(cmd[1])))
	{
		line = ft_printf_to_var("%s\n", ms_find_env_value(ms, "OLDPWD"));
		ft_putstr_fd(line, aux);
		chdir(ms_find_env_value(ms, "OLDPWD"));
	}
	else
		update_env_values(ms, current_cmd, pwd, cmd, aux);
	if (aux != 1)
		close(aux);
}
