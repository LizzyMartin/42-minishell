/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   38_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/10/12 19:33:58 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<_minishell.h>

t_ms	*g_ms = NULL;

void	ms_subshell(t_ms *ms)
{
	ms_add_history(ms, ms->shell_line_tokenized);
	if (ms_tokenizer(ms) == 1)
		return ;
	if (ms_parse(ms) != 1 && ms->no_path == 0)
	{
		ms->i_subs = 0;
		ms_execute(ms);
	}
}

void	minishell(t_ms *ms)
{
	if (ms_read_input(ms) == 1)
		return ;
	ms_subshell(ms);
	ms_reinit(ms);
}

int	main(int argc, char **argv, char **envp)
{
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
		ms_init_history(ms);
		print_banner();
		while (1)
			minishell(ms);
		ms_finish(ms);
		clear_history();
		rl_clear_history();
		get_next_line(-1);
	}
	return (0);
}
