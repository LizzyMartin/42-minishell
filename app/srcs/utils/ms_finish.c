/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:54 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 08:43:38 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_finish(t_ms *ms)
{
	ms_free_history(ms);
	ms_free_env(ms);
	
	ft_free_ptr((void *) ms->readline_var);
	ft_free_ptr((void *) ms->shell_line);
	ft_free_ptr((void *) &(ms->p));
	ft_printf("fechou!\n");
}
