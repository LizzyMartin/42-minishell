#include    <minishell.h>

void    free_env(t_ms *ms)
{
    t_env   *aux;
    t_env   *tmp;

    aux = ms->envs;
    while (aux)
    {
        if (ms->envs->key)
            free(ms->envs->key);
        if  (ms->envs->value)
            free(ms->envs->value);
        tmp = aux->next;
        free(aux);
        aux = tmp;

    }
    ms->envs = NULL;
}
