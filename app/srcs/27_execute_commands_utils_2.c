/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_commands_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/09 17:15:31 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

void	ms_close_fds(t_p *curr_prompt)
{
	if (curr_prompt->input_fd > 0)
		close(curr_prompt->input_fd);
	if (curr_prompt->output_fd > 1)
		close(curr_prompt->output_fd);
}

static int	iterate_cmd_count_cat(t_ms *ms, t_cmd **tmp)
{
	char	*trim;

	trim = NULL;
	trim = ft_strtrim((*tmp)->cmd_line, " ");
	if (ft_strncmp(trim, "cat", ft_strlen(trim)) == 0
		&& (*tmp)->index == 0)
		ms->is_cat_sequence = 1;
	if (ms->is_cat_sequence)
	{
		while (tmp && ft_strncmp(trim, "cat", ft_strlen(trim)) == 0)
		{
			ms->fake_cat_input++;
			(*tmp) = (*tmp)->next;
			ft_free_ptr((void *) &trim);
			if ((*tmp) == NULL)
				break ;
			trim = ft_strtrim((*tmp)->cmd_line, " ");
		}
		ft_free_ptr((void *) &trim);
		return (1);
	}
	ft_free_ptr((void *) &trim);
	return (0);
}

void	pre_cat_ls_sc(t_ms *ms, t_p *curr_prompt)
{
	t_cmd	*tmp;

	if (curr_prompt->args_amount <= 1)
		return ;
	ms->fake_cat_input = 0;
	ms->is_cat_sequence = 0;
	tmp = curr_prompt->cmds;
	while (tmp)
	{
		if (iterate_cmd_count_cat(ms, &tmp) == 1)
			break ;
		tmp = tmp->next;
	}
	if (curr_prompt->args_amount == ms->fake_cat_input)
	{
		ms->is_cat_sequence = 0;
		ms->fake_cat_input = 0;
	}
}

void	exec_cat_ls_sc(t_ms *ms)
{
	char	*input;

	while (ms->is_cat_sequence && ms->fake_cat_input-- > 0)
	{
		input = get_next_line(0);
		ft_free_ptr((void *) &input);
	}
}
