/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:47:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/03/25 18:19:10 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

char	*ft_str_replace_all(char *str, char *search, char *replace)
{
	char	*tmp_str;

	while (ft_strnstr(str, search, ft_strlen(str)) != NULL)
	{
		tmp_str = ft_str_replace(str, search, replace);
		str = tmp_str;
	}
	return (str);
}
