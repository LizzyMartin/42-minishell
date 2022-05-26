/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:56:52 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 19:56:53 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_print_history(t_ms *ms)
{
	t_history	*h;
	int			i;

	i = 1;
	h = ms->history;
	while (h)
	{
		if (h->index != 0 && h->line != NULL)
			ft_printf("  %d  %s", i, h->line);
		i++;
		h = h->next;
	}
}
