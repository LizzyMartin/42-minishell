/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_tokenizer_sintax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relizabe <relizabe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:14:16 by argel             #+#    #+#             */
/*   Updated: 2022/09/29 21:42:19 by relizabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

static int	connectors_are_wrong(t_ms *ms) //
{
	int		i;
	char	*c;

	return (0);
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
	int		size;
	char	*c;

	i = 0;
	c = ms->shell_line;
	size = ft_strlen(c);
	while (c[i])
	{
		if (c[i] == '"' || c[i] == '\'')
			i += ft_str_indexof(c, ft_chr_to_str(c[i], 1), size);
		if (subshell_wrong2(i, c))
			return (1);
		i++;
	}
	return (0);
}

int	dont_confuse_heredoc(t_ms *ms)
{
	char	*c;
	int		i;

	i = 0;
	c = ms->shell_line;
	while (c[i])
	{
		if (c[i] != '<')
			return (0);		
		i++;
	}
	ft_pf_error("miniheaven:%s \n", E_BADSINTAX);
	return (1);
}

int	ms_sintax(t_ms *ms)
{
	if (dont_confuse_heredoc(ms)
	|| connectors_are_wrong(ms)
	|| subshell_wrong(ms))
		return (1);
	return (0);
}
