/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_tokenizer_subshell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/28 02:55:06 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	sub(t_ms *m, t_ms *ms, \
t_p *curr_prompt, t_cmd **current_cmd)
{
	m = &(ms->subs[ms->i_subs]);
	if (curr_prompt->input_fd > 0)
		dup2(curr_prompt->input_fd, 0);
	dup2((*current_cmd)->pipe[1], 1);
	ms_subshell(m);
	ms_reinit(m);
	exit(0);
}

int	execv_in_sub_shell(t_cmd **current_cmd, \
t_p *curr_prompt, int subshell, t_ms *ms)
{
	t_ms	*m;

	m = NULL;
	pipe((*current_cmd)->pipe);
	subshell = fork();
	if (subshell == 0)
		sub(m, ms, curr_prompt, current_cmd);
	waitpid(subshell, NULL, 0);
	curr_prompt->input_fd = (*current_cmd)->pipe[0];
	close((*current_cmd)->pipe[1]);
	ms->i_subs++;
	if ((curr_prompt->pipe_amount - 1) == (*current_cmd)->index)
	{
		ft_fd_print(curr_prompt->input_fd);
		ms->no_path = 1;
		return (2);
	}
	*current_cmd = (*current_cmd)->next;
	return (0);
}

int	ms_execute_prompt_in_subshell(t_ms *ms,
		t_p *curr_prompt, int *exit_code)
{
	int		child;
	t_ms	*current_sub;

	current_sub = &(ms->subs[ms->i_subs]);
	child = fork();
	if (child == 0)
	{
		ms_subshell(current_sub);
		exit(0);
	}
	ms_close_fds(curr_prompt);
	waitpid(child, exit_code, 0);
	(void) ms;
	(void) curr_prompt;
	(void) exit_code;
	return (1);
}

static char	*ms_parse_subshells2(char **str, int i, t_ms *ms)
{
	char	*extract;
	int		start;
	int		end;

	extract = NULL;
	ms_init(&ms->subs[i], ms->argc, ms->argv, ms->envp);
	extract = ft_strdup(*str);
	start = ft_first_ocurrence(extract, '(');
	end = ft_first_ocurrence(extract + start, ')');
	extract = ft_substr(extract + start, 0, end + 1);
	(void) i;
	return (extract);
}

void	ms_parse_subshells(t_ms *ms)
{
	char	*extract;
	int		i;
	char	*tmp;

	i = -1;
	ms->n_subs = 0;
	ms->n_subs = ft_count_chr(ms->shell_line_tokenized, '(');
	if (ms->n_subs == 0)
		return ;
	ms->subs = ft_calloc(ms->n_subs + 1, sizeof(t_ms));
	tmp = ft_strdup(ms->shell_line_tokenized);
	while (++i < ms->n_subs)
	{
		extract = ms_parse_subshells2(&tmp, i, ms);
		ms->subs[i].shell_line = ft_substr(extract + 1, 0,
				ft_strlen(extract) - 2);
		tmp = ft_str_replace(ms->shell_line_tokenized, extract, T_SUBSHELL);
		ms->shell_line_tokenized = tmp;
	}
}
