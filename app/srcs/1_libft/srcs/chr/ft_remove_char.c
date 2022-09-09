/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 00:59:00 by argel             #+#    #+#             */
/*   Updated: 2022/06/07 18:49:38 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_remove_char(char *s, char c)
{
	int	new;
	int	old;

	new = 0;
	old = 0;
	while (s[old])
	{
		if (s[old] != c)
			s[new++] = s[old];
		old++;
	}
	s[new] = '\0';
}
