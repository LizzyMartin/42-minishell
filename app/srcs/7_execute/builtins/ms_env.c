#include <minishell.h>

int	ms_env(t_ms *ms)
{
	t_env	*env;

	env = ms->p.envs;
	while (env)
	{
		if (env->key != NULL && env->value != NULL)
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	ms->p.cmds->exit_status = EXIT_SUCCESS;
	return (ms->p.cmds->exit_status);
}
