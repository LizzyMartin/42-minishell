/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   38_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:03 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/23 03:08:22 by acapela-         ###   ########.fr       */
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
		ms_execute(ms);
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
	// char *str = ft_strdup("__[BANANA5]__|(grep a)|(wc -l)");

	// ft_printf("#%d#\n", ft_first_ocurrence(str, '('));
	// ft_printf("#%d#\n", ft_first_ocurrence(str, ')'));
	
	// char *cut = ft_substr(str + ft_first_ocurrence(str, '('), 0, ft_first_ocurrence(str + ft_first_ocurrence(str, '('), ')'));
	// ft_printf("#%s#\n", cut);

	// exit(0);
	
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
	}
	return (0);
}
