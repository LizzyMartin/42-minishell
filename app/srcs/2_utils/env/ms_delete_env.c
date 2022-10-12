/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_delete_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:57:45 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/13 00:36:35 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<_minishell.h>

void	ms_delete_env(t_env **envs, char *key)
{
	t_env	*aux;
	t_env	*delete;
	
	aux = (*envs);
	while (aux)
	{
		if (ft_strncmp(aux->key, key, ft_strlen(aux->key)) == 0)
		{
			delete = aux;
			if (aux->next != NULL && aux->prev == NULL) // primeiro
			{
				aux = aux->next;
				aux->prev = NULL;
				*envs = aux;
			}
			else if (aux->next != NULL && aux->prev != NULL) // meio
			{
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;
			}
			else if (aux->next == NULL && aux->prev != NULL) // ultimo
				aux->prev = NULL;
			else
				*envs = NULL;
			free(delete->key);
			free(delete->value);
			free(delete);
			break ;
		}
		aux = aux->next;
	}
}
