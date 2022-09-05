/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/03 21:36:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_switch_subshell_output(t_ms *ms)
{
	(void) ms;
}

int		ms_execute_prompt_in_subshell(t_ms *ms, t_p *curr_prompt, int *exit_code)
{
	int		len;
	int		child;
	t_ms	*current_sub;

	len = ft_strlen(curr_prompt->this_p_line);
	if (ft_strnstr(curr_prompt->this_p_line, T_SUBSHELL, len) != NULL)
	{
		current_sub = &(ms->subs[ms->i_subs]);
		child = fork();
		if (child == 0)
		{
			printf("AGORA VOU EXECUTAR %s", current_sub->shell_line);
			ms_subshell(current_sub)
			ms_switch_subshell_output(ms);
			exit(0);
		}
		ms->i_subs++;
	}
	else
		return (0);
	(void) exit_code;
	return (1);
}

void	ms_parse_subshells(t_ms *ms)
{
	char	*extract;
	char	*tmp;
	int		i;
	int		len;

	i = -1;
	ms->n_subs = 0;
	// count subshell:
	ms->n_subs = ft_count_chr(ms->shell_line_tokenized, '(');
	if (ms->n_subs == 0)
		return ;
	// malloc according subshells number:
	ms->subs = ft_calloc(ms->n_subs + 1, sizeof(t_ms));

	// iterate subs
	while (++i < ms->n_subs)
	{
		// extract subshell
		extract = ft_substr(ms->shell_line_tokenized, 
			ft_first_ocurrence(ms->shell_line_tokenized, '('),
			ft_first_ocurrence(ms->shell_line_tokenized, ')') + 1);
		len = ft_strlen(extract);
		
		// set on variable
		ms->subs[i].shell_line = ft_substr(extract + 1, 0, len - 2);
		
		// tokenize main shell_line
		tmp = ft_strdup(ms->shell_line_tokenized);
		ft_free_ptr((void *) &ms->shell_line_tokenized);

		// replace
		ms->shell_line_tokenized = ft_str_replace(tmp, extract, T_SUBSHELL);
		ft_free_ptr((void *) &extract);
	}
}
