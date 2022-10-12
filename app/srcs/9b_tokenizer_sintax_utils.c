/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9b_tokenizer_sintax_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:14:16 by argel             #+#    #+#             */
/*   Updated: 2022/10/12 19:26:02 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_minishell.h>

int	all_equal(t_ms *ms)
{
	int		i;
	int		len;
	char	c;

	len = ft_strlen(ms->shell_line);
	i = 0;
	c = ms->shell_line[0];
	if (c != '\"' && c != '\'')
		return (0);
	while (i < len)
	{
		if (ms->shell_line[i] != c)
			return (0);
		i++;
	}
	ft_pf_error("miniheaven: %s\n", E_CMDNOTFOUND);
	return (1);
}
