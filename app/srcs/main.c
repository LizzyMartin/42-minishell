/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/03 14:21:27 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   <minishell.h>

int	main(int argc, char **argv, char **envp)
{	
	t_ms	*ms;

	ms = NULL;
	if (argc != 1)
	{
		ft_putstr_fd("miniheaven: wrong number of arguments", 2);
		exit (0);
	}
	ms_init(&ms, argc, argv, envp);
	while (1)
		minishell(ms);
	ms_finish(ms);
	return (0);
}
