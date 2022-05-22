#include <minishell.h>

void	update_env_value(t_ms *ms, char *key, char *value)
{
	t_env	*env;

	env = ms->p.envs;
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(env->key)) == 0) && \
		(env->key != NULL && env->value != NULL))			
			env->value = value;
		env = env->next;
	}
}

int	ms_cd(t_ms *ms)
{
	char		*oldpwd;
	char		pwd[999];
	char		**cmd;
	//char		*dir;

	cmd = ms->p.line_splited;
	oldpwd = find_env_value(ms, "PWD");
	ms->p.cmds->exit_status = 0;
	if (!is_in_env(ms, "OLDPWD"))
		add_env(ms, "OLDPWD", find_env_value(ms, "HOME"));
	if (!cmd[1] || !ft_strncmp(cmd[1], "~", ft_strlen(cmd[1]))
			|| !ft_strncmp(cmd[1], "--", ft_strlen(cmd[1])))
	{
		chdir(find_env_value(ms, "HOME"));
	}
	else if (!ft_strncmp(cmd[1], "-", ft_strlen(cmd[1])))
	{
		ft_printf("%s\n", find_env_value(ms, "OLDPWD"));
		chdir(find_env_value(ms, "OLDPWD"));
	}
	else if (oldpwd)
	{
		// dir = ft_strjoin(oldpwd, "/");
		// dir = ft_strjoin(dir, cmd[1]);
		// ft_printf("%s\n", dir);
		if (chdir(cmd[1]) == -1)
		{
			ft_printf("cd: %s: No such file or directory\n", cmd[1]);
			ms->p.cmds->exit_status = 1;
		}
		else
		{
			getcwd(pwd, 999);
			update_env_value(ms, "OLDPWD", oldpwd);
			update_env_value(ms, "PWD", pwd);
		}
	}
	return (ms->p.cmds->exit_status);
}
