/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_connectors_vs_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:09:38 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/14 13:53:29 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ms_treating_having_quotes_3(t_ms *ms, int i, int size, char *line)
{
	char	*tmp;

	if (ft_strnstr(line, "&&", ft_strlen(line)))
	{
		tmp = ft_substr(line, i, size - i);
		char *tmp2 = \
			ft_str_replace_all(tmp, \
		"&&", T_CONNECTOR);
		ms->aux = ft_strjoin_free(ms->aux, tmp2);
	}
	if (ft_strnstr(line, "||", ft_strlen(line)))
	{
		tmp = ft_substr(line, i, size - i);
		char *tmp2 = \
			ft_str_replace_all(tmp, \
		"||", T_CONNECTOR);
		ms->aux = ft_strjoin_free(ms->aux, tmp2);
	}
	if (ft_strnstr(line, "|", ft_strlen(line)))
	{
		tmp = ft_substr(line, i, size - i);
		char *tmp2 = \
			ft_str_replace_all(tmp, \
		"|", T_PIPE);
		ms->aux = ft_strjoin_free(ms->aux, tmp2);
	}
	else
	{
		tmp = ft_substr(line, i, size - i);
		ms->aux = ft_strjoin_free(ms->aux, tmp);
	}
}

static void	ms_treating_having_quotes_2(t_ms *ms, int *i, char *line, int i_aux)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line + *i, 0, i_aux);
	*i += i_aux - 1;
	tmp2 = ft_strdup(tmp);
	ft_free_ptr((void *) &tmp);
	tmp = ft_str_replace_all(tmp2, "&&", T_CONNECTOR);
	tmp2 = ft_strdup(tmp);
	ft_free_ptr((void *) &tmp);
	tmp = ft_str_replace_all(tmp2, "||", T_CONNECTOR);
	tmp2 = ft_strdup(tmp);
	ft_free_ptr((void *) &tmp);
	tmp = ft_str_replace_all(tmp2, "|", T_PIPE);
	tmp2 = ft_strdup(ms->aux);
	ft_free_ptr((void *) &ms->aux);
	ms->aux = ft_strjoin_free(tmp2, tmp);
	ft_free_ptr((void *) &tmp);
}

static void	ms_treating_having_quotes(t_ms *ms, int *i, int size, char *line)
{
	int		index_double;
	int		index_single;
	int		i_aux;

	if (line[*i] == '"' || line[*i] == '\'')
		*i += ms_jump_to_end_quote(ms, line, i, size);
	else
	{
		index_double = ft_str_indexof(line + *i, "\"", size);
		index_single = ft_str_indexof(line + *i, "\'", size);
		if (index_double != -1 || index_single != -1)
		{
			if (index_double != -1 && index_single \
				!= -1 && index_double < index_single)
				i_aux = index_double;
			else if (index_double != -1 && index_single \
				!= -1 && index_single < index_double)
				i_aux = index_single;
			if (index_double != -1 && index_single == -1)
				i_aux = index_double;
			else if (index_single != -1 && index_double == -1)
				i_aux = index_single;
			ms_treating_having_quotes_2(ms, i, line, i_aux);
		}
		else
		{
			ms_treating_having_quotes_3(ms, *i, size, line);
			*i = size - 1;
			return ;
		}
	}
}

void	ms_quotes_vs_connectors(t_ms *ms, char *line)
{
	int		i;
	int		size;

	i = 0;
	size = (int) ft_strlen(line);
	if (ms_check_if_have_quotes(ms, line) == 1)
		return ;
	ms->aux = ft_strdup("");
	while (line[i])
	{
		ms_treating_having_quotes(ms, &i, size, line);
		i++;
	}
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ms->shell_line_tokenized = ft_strdup(ms->aux);
}
