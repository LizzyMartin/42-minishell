/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:47 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 18:11:55 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ms_print_sh_name(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_printf_to_var("%s%s%s %s%s%s ", \
			BOLD_BLUE, SHELL, END_COLOR, BOLD_CYAN, cwd, END_COLOR));
	else
		return (ft_printf_to_var("%s", SHELL));
}

static void	ms_count_connectors(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms->shell_line[i])
	{
		if ((ms->shell_line[i] == '&' && ms->shell_line[i + 1] == '&') \
			|| (ms->shell_line[i] == '|' && ms->shell_line[i + 1] == '|'))
			j++;
		i++;
	}
	ms->connectors_amount = j;
}

int	ms_read_input(t_ms *ms)
{
	ms->sh_name = ms_print_sh_name();
	ms_read_input_signals();
	ms->shell_line = readline(ms->sh_name);
	ft_free_ptr((void *) &ms->sh_name);
	if (ft_strnstr(ms->shell_line, "&&", ft_strlen(ms->shell_line)) \
	!= NULL || ft_strnstr(ms->shell_line, "||", ft_strlen(ms->shell_line)) \
	!= NULL )
		ms_count_connectors(ms);
	if (!ms->shell_line)
	{
		ctrl_d_exit_shell(SIGQUIT);
		exit(0);
	}
	else if (*(ms->shell_line) == '\0')
		return (1);
	return (0);
}
