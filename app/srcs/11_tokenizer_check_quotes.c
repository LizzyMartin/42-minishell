/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_tokenizer_check_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/26 21:27:18 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	ms_count_char(char *str, char c)
{
	int		count;
	char	*iter;
	int		i;

	i = 0;
	count = 0;
	iter = ft_strdup(str);
	while (iter[i])
	{
		if (iter[i] == c)
			count++;
		i++;
	}
	ft_free_ptr((void *) &iter);
	return (count);
}

static void	treat_having_quotes_2(t_ms *ms, char *tmp, int *i, int size)
{
	int		final;
	char	*tmp2;

	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ms->shell_line_tokenized = tmp;
	final = size - *i + 1;
	if (final != -1)
	{
		tmp2 = ft_substr(ms->shell_line, *i + 1, final);
		tmp = ft_printf_to_var("%s %s", \
		ms->shell_line_tokenized, tmp2);
		ft_free_ptr((void *) &tmp2);
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		ms->shell_line_tokenized = tmp;
	}
}

static void	treat_having_quotes(t_ms *ms, char *tmp, int *i, char *aux)
{
	int		first;
	int		second;
	char	*line_inside_quotes;
	int		size;
	char	*aux2;

	size = (int) ft_strlen(ms->shell_line) - 1;
	first = *i;
	aux = ft_chr_to_str(ms->shell_line[*i], 1);
	second = ft_str_indexof(ms->shell_line + first + 1, \
	aux, size - *i);
	ft_free_ptr((void *) &aux);
	line_inside_quotes = ft_substr(ms->shell_line, first + 1, second);
	aux = ft_str_replace_all(line_inside_quotes, " ", T_SPACE);
	aux2 = ft_substr(ms->shell_line, 0, *i);
	tmp = ft_printf_to_var("%s %c%s%c", aux2, \
	ms->shell_line[*i], aux, ms->shell_line[*i]);
	*i += second + 1;
	ft_free_ptr((void *) &aux);
	ft_free_ptr((void *) &aux2);
	treat_having_quotes_2(ms, tmp, i, size);
}

int	get_index_before_space(t_ms *ms, int size, char **cmd)
{
	char	*tmp;
	char	*aux;
	int		index;

	tmp = cmd[0];
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ms->shell_line_tokenized = ft_strdup(tmp);
	aux = ft_chr_to_str(' ', 1);
	index = ft_str_indexof(ms->shell_line, aux, size);
	ft_free_ptr((void *) &aux);
	return (index);
}

void	ms_check_quotes(t_ms *ms)
{
	int		i;
	char	**cmd;
	char	*tmp;
	int		size;
	char	*aux;

	aux = NULL;
	cmd = ft_split(ms->shell_line, ' ');
	tmp = ft_strdup(cmd[0]);
	if (ft_strchr(ms->shell_line_tokenized, '\'') || \
		ft_strchr(ms->shell_line_tokenized, '"'))
	{
		size = (int) ft_strlen(ms->shell_line) - 1;
		i = ms_get_index(ms, size, cmd);
		while (ms->shell_line[i])
		{
			if (ms->shell_line[i] == '"' || ms->shell_line[i] == '\'')
				treat_having_quotes(ms, tmp, &i, aux);
			i++;
		}
	}
	ft_free_ptr((void *) &tmp);
	ft_mtx_free((void **) cmd);
}
