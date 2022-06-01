/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sintax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:14:16 by argel             #+#    #+#             */
/*   Updated: 2022/05/31 21:46:04 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			if (c[i + 2] == c[i])
			{
				ft_pf_error("miniheaven:%s '%c'\n", E_BADSINTAX, c[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ms_sintax(t_ms *ms)
{
	return (connectors_are_wrong(ms));
}
