/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_tokenizer_sintax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:14:16 by argel             #+#    #+#             */
/*   Updated: 2022/09/23 04:17:20 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static int	connectors_are_wrong(t_ms *ms)
{
	int		i;
	char	*c;

	i = 0;
	c = ms->shell_line;
	while (c[i])
	{
		if (c[i] == '&' || c[i] == '|' || c[i] == ';' || c[i] == '>')
		{
			if (c[i + 2] == '\0' || c[i + 2] == c[i])
			{
				ft_pf_error("miniheaven:%s '%c'\n", E_BADSINTAX, c[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	subshell_wrong2( int i, char *c)
{
	int		len;

	len = ft_strlen(c);
	if ((c[i] == '(' && ft_count_chr(c, ')') == 0)
		|| (c[i] == ')' && ft_count_chr(c, '(') == 0))
	{
		ft_pf_error("miniheaven:%s '%c'\n", E_BADSINTAX, c[i]);
		return (1);
	}
	if (c[i] == ')' && i != len - 1)
	{
		if (ft_strnstr(c + i + 1, "|", len) == NULL
			&& ft_strnstr(c + i + 1, "||", len) == NULL
			&& ft_strnstr(c + i + 1, "&&", len) == NULL)
		{
			ft_pf_error("miniheaven:%s \n", E_BADSINTAX);
			return (1);
		}
	}
	return (0);
}

static int	subshell_wrong(t_ms *ms)
{
	int		i;
	char	*c;

	i = 0;
	c = ms->shell_line;
	while (c[i])
	{
		if (subshell_wrong2(i, c))
			return (1);
		i++;
	}
	return (0);
}

static int	more_sintax_checks(t_ms *ms)
{
	char	*c;
	int		end;

	c = ms->shell_line;
	end = ft_strlen(c) - 1;
	if (c[end] == '|' || c[end] == '&' || !ft_isalpha(c[end]))
	{
		ft_pf_error("miniheaven:%s '%s' \n", E_BADSINTAX, c[end]);
		return (1);
	}
	return (0);
}

int	ms_sintax(t_ms *ms)
{
	if (connectors_are_wrong(ms) \
	|| subshell_wrong(ms)
	|| more_sintax_checks(ms))
		return (1);
	return (0);
}
