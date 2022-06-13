/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_reinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:05:57 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/12 23:26:26 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_reinit(t_ms *ms)
{
	ft_free_ptr((void *) &ms->tmp);
	ft_free_ptr((void *) &ms->tmp2);
	ft_free_ptr((void *) &ms->aux);
	ms_free_prompt(ms, ms->p);
	ft_free_ptr((void *) &ms->sh_name);
	ft_free_ptr((void *) &ms->shell_line);
	ft_free_ptr((void *) &ms->qs);
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ft_mtx_free((void **) ms->slt_splited_by_connectors);
}
