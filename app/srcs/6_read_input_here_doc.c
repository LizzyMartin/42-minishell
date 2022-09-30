/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_read_input_here_doc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relizabe <relizabe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:42 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/29 21:48:21 by relizabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	interrupt_here_doc(int signal)
{
	(void)signal;
	exit(0);
}

static void	ms_here_doc_loop(char **stdin_text, t_p *p)
{
	ft_putstr_fd("> ", 0);
	ft_putstr_fd(*stdin_text, p->pipe_here_doc[1]);
	if (*stdin_text)
		ft_free_ptr((void *) &(*stdin_text));
	*stdin_text = readline(NULL);
	ft_putstr_fd("\n", p->pipe_here_doc[1]);
}

static void	ms_create_here_doc_document(t_ms *ms, t_p *p, int *hdoc)
{
	char	*tmp;
	char	*stdin_text;

	ft_putstr_fd("> ", 0);
	stdin_text = NULL;
	signal(SIGQUIT, SIG_IGN);
	stdin_text = readline(NULL);
	tmp = ft_printf_to_var("%s\n", p->hd_limiter);
	while (ms->here_doc_open == 1 \
	&& ft_strncmp(stdin_text, tmp, ft_strlen(stdin_text)) != 0)
		ms_here_doc_loop(&stdin_text, p);
	if (stdin_text == NULL)
	{
		ft_printf_to_fd(1, "miniheaven: warning: \
here-document at line %d delimited by end-of-file (wanted `%s')\n", \
		*hdoc, p->hd_limiter);
	}
	ft_free_ptr((void *) &stdin_text);
	ft_free_ptr((void *) &tmp);
	ft_free_ptr((void *) &p->hd_limiter);
}

int	ms_here_doc(t_ms *ms, t_p *p, int *hdoc)
{
	int		here_doc_process;
	int		exit_code;

	ms->here_doc_open = 1;
	pipe(p->pipe_here_doc);
	here_doc_process = fork();
	if (here_doc_process == 0)
	{
		signal(SIGINT, interrupt_here_doc);
		ms_create_here_doc_document(ms, p, hdoc);
		get_next_line(-1);
		ms->here_doc_open = 0;
		exit(0);
	}
	waitpid(here_doc_process, &exit_code, 0);
	ms->here_doc_open = 0;
	close (p->pipe_here_doc[1]);
	return (p->pipe_here_doc[0]);
}
