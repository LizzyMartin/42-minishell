#include <minishell.h>

int is_environ(t_ms *ms, char *var, char **env_var_cont)
{
	int i;
	char **envp;
	char **envp_splitted;

	i = 0;
	envp = ms->envp;
	var++;
	while (envp[i])
	{
		envp_splitted = ft_split(envp[i], '=');
		if (ft_strncmp(envp_splitted[0], var, ft_strlen(envp_splitted[0])) == 0)
		{
			*env_var_cont = ft_strdup(envp_splitted[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ms_echo(t_ms *ms)
{
	int i;
	char	*env_var_cont;
	int	has_flag;

	i = 0;
	if(!ms->p.line_splited[1])
	{
		ft_printf("\n");
		return (0);
	}
	has_flag = ft_strncmp(ms->p.line_splited[1], "-n", ft_strlen(ms->p.line_splited[1]));
	while(i++ < ms->p.cmds_size)
	{
		if (ms->p.line_splited[i] && ms->p.line_splited[i][0] == '$')
		{
			if (is_environ(ms, ms->p.line_splited[i], &env_var_cont) == 1)
				ft_printf("%s", env_var_cont);
		}
		else
		{
			ft_printf("%s", ms->p.line_splited[i]);
		}
	}
	if (has_flag)
		ft_printf("\n");
	ms->p.cmds->exit_status = 0;
	return (ms->p.cmds->exit_status);
}

/*//// echo ////

echo => '\n'

echo -n => ''

echo alguma coisa => 'alguma coisa\n'

echo -n alguma coisa => 'alguma coisa'

echo $PWD => '/home/user/ \n'

echo $PWD oi => '/home/user/ oi\n'

echo $pwd => '\n'

echo $pwd oi => 'oi\n'

echo \\\\\\\\\\\\\\\\\\\\ => '\n\\\\\' (a cada //// escrever //)

*/
