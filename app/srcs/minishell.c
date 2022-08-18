/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:06 by acapela-          #+#    #+#             */
/*   Updated: 2022/08/18 13:15:10 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell(t_ms *ms)
{
	if (ms_read_input(ms) == 1)
		return ;
	if (ms_tokenizer(ms) == 1)
		return ;
	if (ms_parse(ms) != 1 && ms->no_path == 0)
		ms_execute(ms);
	ms_reinit(ms);
}
