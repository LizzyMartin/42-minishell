#include    <minishell.h>

void    free_env(t_ms *ms)
{
    t_env   *aux;
    t_env   *tmp;

    aux = ms->p.envs;
    while (aux)
    {
        if (ms->p.envs->key)
            free(ms->p.envs->key);
        if  (ms->p.envs->value)
            free(ms->p.envs->value);
        tmp = aux->next;
        free(aux);
        aux = tmp;

    }
    ms->p.envs = NULL;
}
