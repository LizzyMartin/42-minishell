#include    <minishell.h>

void    delete_env(t_ms *ms, char *key)
{
    t_env   *aux;
    t_env   *tmp;

    tmp = ms->p.envs;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
        {
            aux->next = tmp->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            return ;
        }
        else
            aux = tmp;
        tmp = tmp->next;
    }
}
