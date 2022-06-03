/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:06 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 16:30:09 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell(t_ms *ms)
{
	if (ms_read_input(ms) == 1)
		return ;
	if (ms_tokenizer(ms) == 1)
		return ;
	ms_parse(ms);
	ms_execute(ms);
	ms_reinit(ms);
}
