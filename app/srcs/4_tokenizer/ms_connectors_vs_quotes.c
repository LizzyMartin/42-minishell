/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_connectors_vs_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:09:38 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/13 21:18:28 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ms_jump_to_end_quote(t_ms *ms, char *line, int *i, int size)
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

static void	ms_treating_having_quotes_3(t_ms *ms, char *line)
{
	char	*tmp;

	if (ft_strnstr(line, "&&", ft_strlen(line)))
	{
		tmp = ft_strdup(line);
		ft_free_ptr((void *) &line);
		ms->shell_line_tokenized = \
			ft_str_replace_all(tmp, \
		"&&", T_CONNECTOR);
	}
	if (ft_strnstr(line, "||", ft_strlen(line)))
	{
		tmp = ft_strdup(line);
		ft_free_ptr((void *) &line);
		ms->shell_line_tokenized = \
			ft_str_replace_all(tmp, \
		"||", T_CONNECTOR);
	}
	if (ft_strnstr(line, "|", ft_strlen(line)))
	{
		tmp = ft_strdup(line);
		ft_free_ptr((void *) &line);
		ms->shell_line_tokenized = \
			ft_str_replace_all(tmp, \
		"|", T_PIPE);
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
	int		d_i;
	int		s_i;
	int		i_aux;

	if (line[*i] == '"' || line[*i] == '\'')
		*i += ms_jump_to_end_quote(ms, line, i, size);
	else
	{
		ft_printf("ENTREI\n");
		d_i = ft_str_indexof(line + *i, "\"", size);
		s_i = ft_str_indexof(line + *i, "\'", size);
		if (d_i != -1 || s_i != -1)
		{
			if (d_i < s_i)
				i_aux = d_i;
			else
				i_aux = s_i;
			ms_treating_having_quotes_2(ms, i, line, i_aux);
		}
		else
		{
			ms_treating_having_quotes_3(ms, line);
			return ;
		}
	}
}

void	ms_quotes_vs_connectors(t_ms *ms, char *line)
{
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(line);
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
