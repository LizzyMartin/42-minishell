#include    <minishell.h>

char    *find_env_value(t_ms *ms, char *key)
{
    t_env   *aux;

    aux = ms->p.envs;
    while (aux)
    {
        if (!ft_strncmp(aux->key, key, ft_strlen(key)))
            return (aux->value);
        aux = aux->next;
    }
    return (ft_strdup(""));
}
