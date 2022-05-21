#include	<minishell.h>

void	delete_env(t_ms *ms, char *key)
{
    t_env	*env;
   // t_env	*del;
    t_env	*before;
    t_env	*after;
	
	env = ms->p.envs;
    before = env;
    after = env->next;
    ft_printf("%s %s\n", env->key, key);

    while (env->key != NULL && ft_strncmp(env->key, key, ft_strlen(env->key)) != 0)
    {
        before = env;
        env = env->next;
        after = after->next;
    }
    ft_printf("%s %s %s\n", before->key, env->key, after->key);
}
