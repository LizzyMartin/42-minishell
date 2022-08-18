/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:26:04 by acapela-          #+#    #+#             */
/*   Updated: 2022/06/14 18:58:25 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_boolean(const char *wildcard, const struct dirent *de, int all)
{
	return ((all == 1 && ((ft_strncmp(de->d_name, ".", \
			ft_strlen(de->d_name)) == 0) || (ft_strncmp(de->d_name, \
			"..", ft_strlen(de->d_name)) == 0))) || (all == 0 \
			&& (ft_strnstr(de->d_name, wildcard + 1, \
			ft_strlen(de->d_name)) == NULL)));
}

void	update_tmp(char **replace, DIR *dr, struct dirent **de, char **tmp)
{
	(*tmp) = ft_strjoin_free((*replace), " ");
	(*replace) = ft_strjoin_free((*tmp), (*de)->d_name);
	(*tmp) = ft_strjoin((*replace), " \0");
	(*de) = readdir(dr);
}

int	valid_chr(char chr)
{
	if (chr != '\'' && chr != '\"' \
		&& chr != '\0' && chr != ' ')
		return (1);
	return (0);
}
