#include <minishell.h>

void	update_env_value(t_ms *ms, char *key, char *value)
{
	t_env	*env;

	env = ms->envs;
	while (env)
	{
		if ((ft_strncmp(env->key, key, ft_strlen(env->key)) == 0) && \
			(env->key != NULL && env->value != NULL))
            {
                ft_free_ptr((void *) &env->value);
			    env->value = ft_strdup(value);
            }
		env = env->next;
	}
}
