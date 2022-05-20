#include <minishell.h>

void	init_env(t_ms *ms)
{
	int		i;
	char	**envp;
	char	**envp_splitted;

	i = 0;
	envp = ms->envp;
	ms->p.envs = malloc(sizeof(struct s_env));
	while (envp[i])
	{
		envp_splitted = ft_split(envp[i], '='); //alterar para o parse_env
		add_env(ms, envp_splitted[0], envp_splitted[1]);
		i++;
	}
}
