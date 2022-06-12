/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/11 22:34:11 by acapela-         ###   ########.fr       */
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
	// if (argc || argv || envp)
	// {
		
	// }
	// char *s = ft_strdup("exit_BANANA3_wc");
 	// char *token = ft_strdup("_BANANA3_");
 	// char **split = ft_split_by_str(s, token);

 	// ft_printf("#%s#\n", split[0]);
	// ft_mtx_free((void **)split);
	// ft_free_ptr((void *) &s);
	// ft_free_ptr((void *) &token);
	return (0);
}
