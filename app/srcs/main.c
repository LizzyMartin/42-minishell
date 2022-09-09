/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 00:12:27 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

t_ms	*g_ms = NULL;

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	child1;
	i = 0;

	while (i < 2)
	{
		child1 = fork();
		ft_printf("TESTE\n");
		if (child1 == 0)
		{
			int child2 = fork();
			if (child2 == 0)
			{
				printf("EU SOU O FILHO! PID: %ld%ld\n", (long)getpid(), (long)getppid());
			}
			// else
			// 	exit(0);
		}
		else
		{
			waitpid(child1, NULL, 0);
			printf("EU SOU O PAI! PID: %ld%ld\n", (long)getpid(), (long)getppid());
		}
		i++;
	}
			// else
			// 	exit(0);
		
			exit(0);

	t_ms	*ms;

	ms = NULL;
	if (argc > 1 || argv[1] != NULL)
	{
		ft_putstr_fd("miniheaven: invalid arguments\n", 2);
		exit (0);
	}
	else
	{
		ms = ft_calloc(1, sizeof(t_ms));
		g_ms = ms;
		ms_init(ms, argc, argv, envp);
		print_banner();
		while (1)
			minishell(ms);
		ms_finish(ms);
	}
	return (0);
}
