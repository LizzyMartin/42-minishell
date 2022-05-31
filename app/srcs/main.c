/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 15:19:31 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include   <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = NULL;
	ms_init(&ms, argc, argv, envp);
	while (1)
		minishell(ms);
	ms_finish(ms);
	return (0);
}
