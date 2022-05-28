/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:00:23 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 22:29:30 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free_env(t_ms *ms)
{
	t_env	*delete;
    t_env   *stack;

    stack = ms->envs;
	while (stack != NULL)
	{
		delete = stack;
		stack = stack->next;
	 	if (delete && delete->value)e));
		ite && delete->key);
			ft_free_ptr((void **) &(delete->key));
		ft_free_ptr((void **) &delete);
	}
    ms->envs = NULL;
}
