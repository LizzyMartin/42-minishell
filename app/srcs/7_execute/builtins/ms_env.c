#include <minishell.h>

void	ms_env(t_ms *ms)
{
	t_env	*env;
    

	env = ms->envs;
	while (env)
	{
		if (env->key != NULL && env->value != NULL)
		{
            
			ft_printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	ms->p.cmds->exit_code = EXIT_SUCCESS;
}
