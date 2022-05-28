/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:00:23 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/28 01:32:56 by argel            ###   ########.fr       */
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
		//ft_free_ptr((void *) &(delete->value));
		//ft_free_ptr((void *) &(delete->key));
		ft_free_ptr((void *) &delete);
		stack = stack->next;
	}
    ms->envs = NULL;
}
