/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:06 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 14:35:44 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell(t_ms *ms)
{

	
	
	char *teste = NULL;
	teste = get_next_line(0);
	ft_putstr_fd(teste, 1);
	teste = get_next_line(0);
	ft_putstr_fd(teste, 1);


	if (0)
	{
	if (ms_read_input(ms) == 1)
		return ;

	if (ms_tokenizer(ms) == 1)
		return ;
	ms_parse(ms);
	ms_execute(ms);
	ms_reinit(ms);
	}
}
