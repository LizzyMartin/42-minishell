/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/30 22:32:15 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include   <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = NULL;
	ms_init(&ms, argc, argv, envp);
	//while (1)
		minishell(ms);
	ms_finish(ms);
	return (0);
}
