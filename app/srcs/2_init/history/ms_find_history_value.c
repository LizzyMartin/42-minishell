#include    <minishell.h>

char    *find_env_value(t_ms *ms, char *key)
{
    t_env   *env;

    env = ms->p.envs;
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(env->key)) == 0) && \
        (env->key != NULL && env->value != NULL))			
            return (env->value);
		env = env->next;
	}
    return (ft_strdup(""));
}
