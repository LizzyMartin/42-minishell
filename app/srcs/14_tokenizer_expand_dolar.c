/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_tokenizer_expand_dolar.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:55:01 by argel             #+#    #+#             */
/*   Updated: 2022/09/09 20:28:34 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	threat_dolar(t_ms *ms, char **line_splited, int i, char *dolar_cmd)
{
	int		final;
	int		j;

	j = 0;
	while (line_splited[i][j])
	{
		if (line_splited[i][j] == '$')
		{
			final = 0;
			while (valid_chr(line_splited[i][j + final]))
				final++;
			dolar_cmd = ft_substr((line_splited[i] + j), 0, final);
			ms_has_single_quotes(ms, dolar_cmd, ft_strdup(line_splited[i]));
		}
		j++;
	}
}

static void	ms_quotes_something_2(t_ms *ms, char **line_splited, \
int i, char *dolar_cmd)
{
	char	*tmp;
	char	*aux;

	if (ft_strchr(line_splited[i], '$') == NULL || ms->has_single_quotes)
	{
		tmp = ft_strjoin(ms->shell_line_tokenized, " ");
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		aux = ft_strdup(line_splited[i]);
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		ms->shell_line_tokenized = ft_strjoin(tmp, aux);
		ft_free_ptr((void *) &tmp);
		ft_free_ptr((void *) &aux);
	}
	else
		threat_dolar(ms, line_splited, i, dolar_cmd);
}

static void	ms_quotes_something_1(t_ms *ms, char **line_splited, int i)
{
	int	index_double;
	int	index_single;

	index_double = ft_str_indexof(line_splited[i], \
	"\"", ft_strlen(line_splited[i]) - 1);
	index_single = ft_str_indexof(line_splited[i], "'", \
	ft_strlen(line_splited[i]) - 1);
	if (index_double != -1 && index_single \
	!= -1 && index_double < index_single)
		ms->has_double_quotes = 1;
	else if (index_double != -1 && index_single \
	!= -1 && index_single < index_double)
		ms->has_single_quotes = 1;
	if (index_double != -1 && index_single == -1)
		ms->has_double_quotes = 1;
	else if (index_single != -1 && index_double == -1)
		ms->has_single_quotes = 1;
	if (ms_count_char(line_splited[i], '\'') == 1)
		ms->has_single_quotes = 0;
	if (ms_count_char(line_splited[i], '"') == 1)
		ms->has_double_quotes = 0;
}

void	ms_expand_dolar_loop(t_ms *ms, char **line_splited, int i)
{
	char	*dolar_cmd;

	dolar_cmd = NULL;
	ms->has_double_quotes = 0;
	ms->has_single_quotes = 0;
	ms_quotes_something_1(ms, line_splited, i);
	ms_quotes_something_2(ms, line_splited, i, dolar_cmd);
	if (ms->has_double_quotes)
		ft_chr_remove_all(ms->shell_line_tokenized, '"');
	if (ms->has_single_quotes)
		ft_chr_remove_all(ms->shell_line_tokenized, '\'');
}

void	ms_expand_dolar(t_ms *ms)
{
	char		**line_splited;
	int			i;
	t_history	*history_line;
	char		*tmp_exit_code;

	i = -1;
	line_splited = ft_split(ms->shell_line_tokenized, ' ');
	if (line_splited[1] && ft_strncmp(line_splited[1], "$?", 2) == 0)
	{
		history_line = ms_last_history(ms->history);
		tmp_exit_code = ft_itoa(history_line->l_c_exit_code);
		ms->shell_line_tokenized = ft_str_replace_all(ms->shell_line_tokenized,
				"$?", tmp_exit_code);
		ft_free_ptr((void *) &tmp_exit_code);
		ft_mtx_free((void **) line_splited);
		return ;
	}
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ms->shell_line_tokenized = ft_strdup("");
	while (line_splited[++i])
		ms_expand_dolar_loop(ms, line_splited, i);
	ft_mtx_free((void **) line_splited);
}
