#include    <minishell.h>

void    add_env(t_ms *ms, char *key, char *value)
{
    t_env   *aux;

    aux = ms->envs;
	if (!aux)
	{
		aux = (t_env *) malloc(sizeof(struct s_env));
		aux->key = key;
		aux->value = value;
		aux->next = NULL;
		aux->prev = NULL;
	}
	else
	{
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = (t_env *) malloc(sizeof(struct s_env));
		aux->next->key = key;
		aux->next->value = value;
		aux->next->next = NULL;
		aux->next->prev = aux;
	}
}
