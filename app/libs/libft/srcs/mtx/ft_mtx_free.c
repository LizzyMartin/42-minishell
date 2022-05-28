/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtx_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 03:11:26 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 20:59:52 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

void	ft_mtx_free(void **matrix)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (matrix[++i])
			ft_free_ptr((void *) &matrix[i]);
		ft_free_ptr((void *) &matrix);
	}
}
