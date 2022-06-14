/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_connectors_vs_quotes_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:09:38 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 21:18:33 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_replace_connectors_by_token(t_ms *ms, char *tmp)
{
	if (ft_strnstr(ms->shell_line_tokenized, \
	"&&", ft_strlen(ms->shell_line_tokenized)))
	{
		tmp = ft_strdup(ms->shell_line_tokenized);
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		ms->shell_line_tokenized = \
			ft_str_replace_all(tmp, \
		"&&", T_CONNECTOR);
	}
	if (ft_strnstr(ms->shell_line_tokenized, \
	"||", ft_strlen(ms->shell_line_tokenized)))
	{
		tmp = ft_strdup(ms->shell_line_tokenized);
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		ms->shell_line_tokenized = \
			ft_str_replace_all(tmp, \
		"||", T_CONNECTOR);
	}
}

int	ms_check_if_have_quotes(t_ms *ms, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strnstr(line, "\"", ft_strlen(line)) == NULL && \
	ft_strnstr(line, "\'", ft_strlen(line)) == NULL)
	{
		ms_replace_connectors_by_token(ms, tmp);
		if (ft_strnstr(ms->shell_line_tokenized, "|", \
		ft_strlen(ms->shell_line_tokenized)))
		{
			tmp = ft_strdup(ms->shell_line_tokenized);
			ft_free_ptr((void *) &ms->shell_line_tokenized);
			ms->shell_line_tokenized = \
				ft_str_replace_all(tmp, \
			"|", T_PIPE);
		}
		return (1);
	}
	return (0);
}

int	ms_get_index(t_ms *ms, int size, char **cmd)
{
	int	i;

	if (ms->is_aux_env)
		i = 0;
	else
		i = get_index_before_space(ms, size, cmd);
	return (i);
}
