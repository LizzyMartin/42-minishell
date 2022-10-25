/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_tokenizer_expand_dolar_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:55:01 by argel             #+#    #+#             */
/*   Updated: 2022/09/28 19:58:13 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static void	threat_dolar_loop(char **line_splited, \
int j, int *threated, t_ms *ms)
{
	int		final;

	if (line_splited[*(ms->tmp5)][j] == '$' &&
	j != (int)(ft_strlen(line_splited[*(ms->tmp5)]) - 1)
	&& line_splited[*(ms->tmp5)][j + 1] != '$')
	{
		final = 1;
		while (valid_chr(line_splited[*(ms->tmp5)][j + final]))
			final++;
		(*ms->tmp4) = ft_substr((line_splited[*(ms->tmp5)] + j), 0, final);
		if (*threated != 0)
			ms_has_single_quotes(ms, \
	(*ms->tmp4), ft_strdup(ms->shell_line_tokenized), *threated);
		else
			ms_has_single_quotes(ms, \
	(*ms->tmp4), ft_strdup(line_splited[*(ms->tmp5)]), *threated);
		*threated = 1;
	}
}

void	threat_dolar(t_ms *ms,
char **line_splited, int i, char *dolar_cmd)
{
	int		j;
	int		threated;
	char	*tmp;

	j = 0;
	threated = 0;
	while (line_splited[i][j])
	{
		ms->tmp4 = &dolar_cmd;
		ms->tmp5 = &i;
		threat_dolar_loop(line_splited, j,
			&threated, ms);
		j++;
	}
	if (threated == 0)
	{
		tmp = ft_printf_to_var("\
%s %s", ms->shell_line_tokenized, line_splited[i]);
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		ms->shell_line_tokenized = tmp;
	}
}

void	ms_has_single_quotes(t_ms *ms, \
char *dolar_cmd, char *line, int threated)
{
	char	*no_dolar;
	char	*value;
	char	*aux;
	char	*aux2;

	no_dolar = ft_substr(dolar_cmd, 1, ft_strlen(dolar_cmd));
	if (ms_is_in_env(ms, no_dolar))
	{
		value = ms_find_env_value(ms, no_dolar);
		aux = ft_strdup(ms->shell_line_tokenized);
		aux2 = ft_str_replace_all(line, dolar_cmd, value);
		ft_free_ptr((void *) &ms->shell_line_tokenized);
		if (threated != 0)
			ms->shell_line_tokenized = ft_strdup(aux2);
		else
			ms->shell_line_tokenized = ft_printf_to_var \
			("%s %s", aux, aux2);
		ft_free_ptr((void *) &aux);
		ft_free_ptr((void *) &aux2);
	}
	else
		ft_free_ptr((void *) &line);
	ft_free_ptr((void *) &no_dolar);
	ft_free_ptr((void *) &dolar_cmd);
}
