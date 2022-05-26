/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:06 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:38:30 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell(t_ms *ms)
{
	if (ms_read_input(ms) == 1)
		return ;
	ms_tokenizer(ms);
	ms_parse(ms);
	ms_execute(ms);
}
