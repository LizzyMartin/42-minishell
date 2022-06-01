/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:26:04 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/31 22:29:39 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	get_boolean(const char *wildcard, const struct dirent *de, int all)
{
	return ((all == 1 && ((ft_strncmp(de->d_name, ".", \
			ft_strlen(de->d_name)) == 0) || (ft_strncmp(de->d_name, \
			"..", ft_strlen(de->d_name)) == 0))) || (all == 0 \
			&& (ft_strnstr(de->d_name, wildcard + 1, \
			ft_strlen(de->d_name)) == NULL)));
}

void	update_tmp(char **replace, DIR *dr, struct dirent **de, char **tmp)
{
	(*tmp) = ft_strjoin((*replace), " ");
	ft_free_ptr((void *) replace);
	(*replace) = ft_strjoin((*tmp), (*de)->d_name);
	ft_free_ptr((void *) tmp);
	(*tmp) = ft_strjoin((*replace), " \0");
	(*de) = readdir(dr);
}
