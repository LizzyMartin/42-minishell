/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:54:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/11 23:01:35 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	valid_chr(char chr)
{
	if (chr != '\'' && chr != '\"' \
		&& chr != '\0' && chr != ' ')
		return (1);
	return (0);
}

static void	treat_having_quotes(t_ms *ms, char *tmp, int *i)
{
	int		first;
	int		second;
	char	*line_inside_quotes;
	int		final;
	int		size;
	char	*aux;
	char	*aux2;

	size = 0;
	first = *i;
	aux = ft_chr_to_str(ms->shell_line[*i], 1);
	second = ft_str_indexof(ms->shell_line + first + 1, \
	aux, size - *i);
	ft_free_ptr((void *) &aux);
	line_inside_quotes = ft_substr(ms->shell_line, first + 1, second);
	aux = ft_str_replace_all(line_inside_quotes, " ", T_SPACE);
	aux2 = ft_substr(ms->shell_line, 0, *i);
	tmp = ft_printf_to_var("%s %c%s%c", aux2, ms->shell_line[*i], aux, ms->shell_line[*i]);
	*i += second + 1;
	ft_free_ptr((void *) &aux);
	ft_free_ptr((void *) &aux2);
	ms->shell_line_tokenized = tmp;
	aux = ft_chr_to_str(ms->shell_line[*i], 1);
	final = ft_str_indexof(ms->shell_line + *i + 1, aux, size);
	ft_free_ptr((void *) &aux);
	if (final != -1)
	{
		tmp = ft_printf_to_var("%s %s", \
		ms->shell_line_tokenized, ft_substr(ms->shell_line, *i + 1, final));
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		ms->shell_line_tokenized = tmp;
	}
}

static int	get_index_before_space(t_ms *ms, int size, char **cmd)
{
	char	*tmp;
	char	*aux;
	int		index;

	tmp = cmd[0];
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ms->shell_line_tokenized = tmp;
	aux = ft_chr_to_str(' ', 1);
	index = ft_str_indexof(ms->shell_line, aux, size);
	ft_free_ptr((void *) &aux);
	return (index);
}

// static void	ms_basic_replaces(t_ms *ms)
// {
// 	char	*tmp;

// 	if (ft_strnstr(ms->shell_line_tokenized, \
// 		"||", ft_strlen(ms->shell_line_tokenized)))
// 	{
// 		tmp = ft_strdup(ms->shell_line_tokenized);
// 		if (ms->shell_line_tokenized)
// 			ft_free_ptr((void *) &ms->shell_line_tokenized);
// 		ms->shell_line_tokenized = \
// 			ft_str_replace_all(tmp, \
// 		"||", T_CONNECTOR);
// 	}
// 	if (ft_strnstr(ms->shell_line_tokenized, \
// 		"&&", ft_strlen(ms->shell_line_tokenized)))
// 	{
// 		tmp = ft_strdup(ms->shell_line_tokenized);
// 		ft_free_ptr((void *) &ms->shell_line_tokenized);
// 		ms->shell_line_tokenized = \
// 			ft_str_replace_all(tmp, \
// 		"&&", T_CONNECTOR);
// 	}
// 	if (ft_strnstr(ms->shell_line_tokenized, \
// 		"|", ft_strlen(ms->shell_line_tokenized)))
// 	{
// 		tmp = ft_strdup(ms->shell_line_tokenized);
// 		ft_free_ptr((void *) &ms->shell_line_tokenized);
// 		ms->shell_line_tokenized = \
// 			ft_str_replace_all(tmp, \
// 		"|", T_PIPE);
// 	}
// }

void	ms_check_quotes(t_ms *ms)
{
	int		i;
	char	**cmd;
	char	*tmp;
	int		size;

	cmd = ft_split(ms->shell_line, ' ');
	tmp = cmd[0];
	if (ft_strchr(ms->shell_line_tokenized, '\'') || \
		ft_strchr(ms->shell_line_tokenized, '"'))
	{
		size = (int) ft_strlen(ms->shell_line) - 1;
		if (ms->is_aux_env)
			i = 0;
		else
			i = get_index_before_space(ms, size, cmd);
		while (ms->shell_line[i])
		{
			if (ms->shell_line[i] == '"' || ms->shell_line[i] == '\'')
				treat_having_quotes(ms, tmp, &i);
			// ms_basic_replaces(ms);
			i++;
		}
	}
	ft_mtx_free((void **) cmd);
}
