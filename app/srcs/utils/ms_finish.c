/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 19:39:04 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_finish(t_ms *ms)
{
	ms_free_history(ms);
	ms_free_env(ms);
	ft_free_ptr((void *) &ms);
	ft_printf("fechou!\n");
}
