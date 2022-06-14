/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_connectors_vs_quotes_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:09:38 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/14 17:28:27 by acapela-         ###   ########.fr       */
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

int	ms_jump_to_end_quote(t_ms *ms, char *line, int *i, int size)
{
	int		second;
	char	*line_inside_quotes;
	char	*tmp;
	char	*tmp2;

	second = 0;
	tmp = ft_chr_to_str(line[*i], 1);
	second = ft_str_indexof(line + *i + 1, \
	tmp, size - *i);
	ft_free_ptr((void *) &tmp);
	line_inside_quotes = ft_substr(line, *i + 1, second);
	tmp2 = ft_strdup(ms->aux);
	if (ms->aux)
		ft_free_ptr((void *) &ms->aux);
	ms->aux = ft_printf_to_var("%s%c%s%c", tmp2, line[*i], \
	line_inside_quotes, line[*i]);
	ft_free_ptr((void *) &tmp2);
	ft_free_ptr((void *) &line_inside_quotes);
	return (second + 1);
}

void	subs_replace_join_free(char *find, char *replace, \
t_ms *ms, char *line)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(line, ms->i, ft_strlen(line) - ms->i);
	tmp2 = ft_str_replace_all(tmp, find, replace);
	tmp3 = ft_strdup(ms->aux);
	ft_free_ptr((void *) &ms->aux);
	ms->aux = ft_strjoin_free(tmp3, tmp2);
	ft_free_ptr((void *) &tmp2);
}
