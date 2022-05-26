/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:57 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:43:06 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free(t_ms *ms)
{
	ft_free_ptr((void *) ms->readline_var);
	ft_free_ptr((void *) ms->shell_line);
	ft_free_ptr((void *) &(ms->p));
}
