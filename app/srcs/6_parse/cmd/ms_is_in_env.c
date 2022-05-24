#include    <minishell.h>

int    is_in_env(t_ms *ms, const char *key)
{
    t_env   *aux;

    aux = ms->envs;
    while (aux)
    {
        if (!ft_strncmp(aux->key, key, ft_strlen(aux->key)))
            return (1);
        aux = aux->next;
    }
    return (0);
}
