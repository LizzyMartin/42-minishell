/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 01:23:51 by argel             #+#    #+#             */
/*   Updated: 2022/06/01 01:24:10 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_count_chr(char *str, char c)
{
	int	con;
	int	i;
	int	w;

	con = 0;
	w = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && con == 0)
		{
			con = 1;
			w++;
		}
		else if (str[i] == c)
			con = 0;
		i++;
	}
	return (w);
}
