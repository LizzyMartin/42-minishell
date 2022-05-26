/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:53:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 21:34:55 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ms_get_files_that_represent_wildcard(char *wildcard)
{
	char			*replace;
	struct dirent	*de;
	int				all;
	DIR				*dr;

	all = 0;
	replace = ft_strdup("");
	dr = opendir(".");
	if (ft_strncmp(wildcard, "*", ft_strlen(wildcard)) == 0)
		all = 1;
	de = readdir(dr);
	while (de != NULL)
	{
		if ((all == 1 && ((ft_strncmp(de->d_name, ".", \
		ft_strlen(de->d_name)) == 0) || (ft_strncmp(de->d_name, \
		"..", ft_strlen(de->d_name)) == 0))) || (all == 0 \
		&& (ft_strnstr(de->d_name, wildcard + 1, \
		ft_strlen(de->d_name)) == NULL)))
			continue ;
		replace = ft_strjoin(ft_strjoin(replace, " "), de->d_name);
		replace = ft_strjoin(replace, " \0");
		de = readdir(dr);
	}
	closedir(dr);
	return (replace);
}

int	next_space_index(t_ms *ms, int after_asteristic_posi)
{
	char	*tmp;

	tmp = ms->shell_line;
	while (tmp[after_asteristic_posi] != ' '
		&& tmp[after_asteristic_posi] != '\0')
		after_asteristic_posi++;
	return (after_asteristic_posi);
}

int	ms_exist_some_file_with_this_wildcard(char *wildcard)
{
	DIR				*dr;
	struct dirent	*de;
	int				wd_f_o;
	int				exist;

	exist = 0;
	dr = opendir(".");
	de = readdir(dr);
	if (ft_strncmp(wildcard, "*", ft_strlen(wildcard)) == 0)
		return (1);
	while (de != NULL)
	{
		wd_f_o = ft_str_indexof(de->d_name,
				wildcard + 1, ft_strlen(de->d_name));
		if (wd_f_o > 0)
			exist = 1;
		de = readdir(dr);
	}
	closedir(dr);
	return (exist);
}

void	ms_wildcard(t_ms *ms)
{
	char	*iterate_shell_line;
	int		start;
	int		end;
	char	*replace;
	char	*wildcard;

	iterate_shell_line = ms->shell_line_tokenized;
	while (ft_strrchr(iterate_shell_line, '*'))
	{
		replace = ft_strdup("");
		start = ft_indexof(ms->shell_line, '*') + 1;
		end = next_space_index(ms, start) - 1;
		wildcard = ft_substr(ms->shell_line, start, end);
		if (ms_exist_some_file_with_this_wildcard(wildcard) == 1)
		{
			replace = ms_get_files_that_represent_wildcard(wildcard);
			ms->shell_line_tokenized = \
ft_str_replace(ms->shell_line_tokenized, wildcard, replace);
		}
		else
			iterate_shell_line += start;
	}
}
