/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_commands_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:41:00 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/09 22:45:28 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_close_fds(t_p *curr_prompt)
{
	if (curr_prompt->input_fd > 0)
		close(curr_prompt->input_fd);
	if (curr_prompt->output_fd > 1)
		close(curr_prompt->output_fd);
}

static int	iterate_cmd_count_cat(char *trim, int is_cat_sequence, \
t_cmd *tmp, int cat)
{
	if (ft_strncmp(trim, "cat", ft_strlen(trim)) == 0)
		is_cat_sequence = 1;
	if (is_cat_sequence)
	{
		while (tmp->next != NULL
			&& ft_strncmp(trim, "cat", ft_strlen(trim)) == 0)
		{
			cat++;
			tmp = tmp->next;
		}
		is_cat_sequence = 0;
		return (1);
	}
	tmp = tmp->next;
	return (0);
}

void	cat_ls_sc(t_p *curr_prompt)
{
	t_cmd	*tmp;
	int		is_cat_sequence;
	int		cat;
	char	*trim;

	cat = 0;
	is_cat_sequence = 0;
	tmp = curr_prompt->cmds;
	trim = ft_strtrim(tmp->cmd_line, " ");
	while (tmp)
	{
		if (iterate_cmd_count_cat(trim, is_cat_sequence, \
		tmp, cat) == 1)
			break ;
		tmp = tmp->next;
	}
	ft_free_ptr((void *) &trim);
	while (cat-- > 0)
		get_next_line(0);
}
