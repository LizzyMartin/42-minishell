#include	<minishell.h>

void	delete_env(t_ms *ms, char *key)
{
   t_env	*env;

	env = ms->envs;
	while (env)
	{
		if ((env->key != NULL && env->value != NULL))
        {
            if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
			{
                if (env->next != NULL)
                    env->prev->next = env->next;
                else
                    env->prev->next = NULL;
            }
        }
		env = env->next;
	}
}
