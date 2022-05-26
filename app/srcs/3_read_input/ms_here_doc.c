/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:08:09 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ms_here_doc(t_p *p)
{
	char	*stdin_text;
	char	*tmp;

	pipe(p->pipe_here_doc);
	ft_putstr_fd("> ", 0);
	stdin_text = get_next_line(0);
	tmp = ft_printf_to_var("%s\n", p->hd_limiter);
	while (ft_strncmp(stdin_text, tmp, sizeof(stdin_text)) != 0)
	{
		ft_putstr_fd("> ", 0);
		ft_putstr_fd(stdin_text, p->pipe_here_doc[1]);
		if (stdin_text)
			ft_free_ptr((void *) &stdin_text);
		stdin_text = get_next_line(0);
	}
	ft_free_ptr((void *) &stdin_text);
	ft_free_ptr((void *) &tmp);
	get_next_line(-1);
	close (p->pipe_here_doc[1]);
	return (p->pipe_here_doc[0]);
}
