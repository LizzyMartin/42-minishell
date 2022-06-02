/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:06 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/02 15:25:25 by argel            ###   ########.fr       */
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
