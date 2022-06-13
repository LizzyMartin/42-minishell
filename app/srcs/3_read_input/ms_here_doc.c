/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 15:58:47 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ms_here_doc(t_ms *ms, t_p *p)
{
	char	*stdin_text;
	char	*tmp;

	ms->here_doc_open = 1;
	pipe(p->pipe_here_doc);
	ft_putstr_fd("> ", 0);
	stdin_text = NULL;
	stdin_text = get_next_line(0);
	tmp = ft_printf_to_var("%s\n", p->hd_limiter);
	while (ms->here_doc_open == 1 && ft_strncmp(stdin_text, tmp, ft_strlen(stdin_text)) != 0)
	{
		ft_putstr_fd("> ", 0);
		ft_putstr_fd(stdin_text, p->pipe_here_doc[1]);
		if (stdin_text)
			ft_free_ptr((void *) &stdin_text);
		ms_while_executing_commands_signals();
		stdin_text = get_next_line(0);
		ft_free_ptr((void *) &tmp);
		tmp = ft_printf_to_var("%s\n", p->hd_limiter);
	}
	ft_free_ptr((void *) &stdin_text);
	ft_free_ptr((void *) &tmp);
	ft_free_ptr((void *) &p->hd_limiter);
	get_next_line(-1);
	//ms->here_doc_open = 0;
	close (p->pipe_here_doc[1]);
	return (p->pipe_here_doc[0]);
}
