/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_tokenizer_expand_dolar_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:55:01 by argel             #+#    #+#             */
/*   Updated: 2022/09/23 21:04:00 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

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
