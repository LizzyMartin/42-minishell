/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:43:28 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/12 00:09:35 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ms_get_home_value(t_ms *ms)
{
	if (ms_is_in_env(ms, "HOME"))
		return (ms_find_env_value(ms, "HOME"));
	else if (ms_is_in_env(ms, "USER"))
		return (ft_printf_to_var("/home/%s", ms_find_env_value(ms, "USER")));
	else
		return (ft_strdup("/home"));
}

static void	ms_home_value(t_ms *ms)
{
	char	*chr_tmp;
	char	*dupped;
	char	*tmp;
	char	*tmp2;

	chr_tmp = ft_chr_to_str('~', 1);
	tmp2 = ft_strdup(ms_get_home_value(ms));
	dupped = ft_strdup(ms->shell_line_tokenized);
	tmp = ft_str_replace_all(dupped \
			, chr_tmp, tmp2);
	ft_free_ptr((void *) &ms->shell_line_tokenized);
	ft_free_ptr((void *) &chr_tmp);
	ft_free_ptr((void *) &tmp2);
	ms->shell_line_tokenized = tmp;
	ft_free_ptr((void *) &chr_tmp);
}

static void	ms_aux_env(t_ms *ms, int equal_index)
{
	char	*key;
	char	*value;

	key = ft_substr(ms->shell_line_tokenized, 0, \
	equal_index + 1);
	value = ft_substr(ms->shell_line_tokenized, \
	equal_index + 2, ft_strlen(ms->shell_line_tokenized));
	ms_add_env(&ms->aux_envs, key, value);
	ft_free_ptr((void *) &key);
	ft_free_ptr((void *) &value);
}

static void	ms_basic_replaces(t_ms *ms, char *line)
{
	char	*tmp;
	char	*aux;
	int		i;
	int 	i_aux;

	i = 0;
	int size = ft_strlen(line);
	aux = ft_calloc(ft_strlen(line), sizeof(char));
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			int second = ft_str_indexof(line + i + 1, ft_chr_to_str(line[i], 1), size - i);
			char *line_inside_quotes = ft_substr(line, i + 1, second);
			aux = ft_printf_to_var("%s%c%s%c", aux, line[i], line_inside_quotes, line[i]);
			i += second + 1;
		}
		else {
			i_aux = ft_str_indexof(line + i, "\"", size);
			if (i_aux != -1)
			{
				tmp = ft_substr(line + i, 0, i_aux);
				i += i_aux - 1;
				tmp = ft_str_replace_all(tmp, "&&", T_CONNECTOR);
				tmp = ft_str_replace_all(tmp, "||", T_CONNECTOR);
				tmp = ft_str_replace_all(tmp, "|", T_PIPE);
				aux = ft_printf_to_var("%s%s", aux, tmp);
			}
			else 
			{
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
				return ;
			}
		}
		i++;
	}
	ms->shell_line_tokenized = aux;
}

int	ms_tokenizer(t_ms *ms)
{
	int	equal_index;
	int	space_index;

	ms->shell_line_tokenized = ft_strdup(ms->shell_line);
	ms->is_aux_env = 0;
	equal_index = ft_str_indexof(ms->shell_line_tokenized, \
	"=", ft_strlen(ms->shell_line_tokenized));
	space_index = ft_str_indexof(ms->shell_line_tokenized, \
	" ", ft_strlen(ms->shell_line_tokenized));
	if (equal_index != -1 && ms->shell_line_tokenized[equal_index - 1] != ' ')
		ms->is_aux_env = 1;
	if (space_index != -1 && space_index < equal_index)
		ms->is_aux_env = 0;
	if (ms_sintax(ms) == 1)
		return (1);
	if (ms_count_char(ms->shell_line_tokenized, '"') != 1 \
	&& ms_count_char(ms->shell_line_tokenized, '\'') != 1)
		ms_check_quotes(ms);
	ms_basic_replaces(ms, ms->shell_line_tokenized);
	ms_expand_dolar(ms);
	if (ms->is_aux_env)
	{
		ms_aux_env(ms, equal_index);
		return (1);
	}
	ms_home_value(ms);
	ms_wildcard(ms);
	return (0);
}
