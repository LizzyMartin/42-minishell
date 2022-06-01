/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 21:34:20 by acapela-         ###   ########.fr       */
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
