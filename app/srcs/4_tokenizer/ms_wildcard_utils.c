/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:26:04 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/01 16:48:53 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_free_files(t_file **files)
{
	t_file	*del;

	ms_go_start(files);
	while ((*files)->next != NULL)
	{
		del = (*files);
		(*files) = (*files)->next;
		ms_file_delete(&del);
	}
}

t_file	*ms_get_current_directory(void)
{
	struct dirent	*de;
	DIR				*dr;
	t_file			*files;
	t_file			*prev;
	t_file			*start;

	dr = opendir(".");
	de = readdir(dr);
	files = ft_calloc(1, sizeof(t_file));
	start = files;
	while (de != NULL)
	{
		prev = files;
		while (de->d_name[0] == '.')
			de = readdir(dr);
		files->name = ft_strdup(de->d_name);
		files->next = ft_calloc(1, sizeof(t_file));
		files = files->next;
		files->prev = prev;
		de = readdir(dr);
	}
	closedir(dr);
	return (start);
}

void	ms_file_delete(t_file **head)
{
	t_file	*prev;
	t_file	*del;

	if (!(*head)->prev)
	{
		*head = (*head)->next;
		ft_free_ptr((void *) &(*head)->prev->name);
		ft_free_ptr((void *) &(*head)->prev);
	}
	else if (!(*head)->next)
	{
		ft_free_ptr((void *) &(*head)->name);
		ft_free_ptr((void *) &(*head));
	}
	else
	{
		prev = (*head)->prev;
		del = *head;
		*head = (*head)->next;
		prev->next = *head;
		(*head)->prev = prev;
		ft_free_ptr((void *) &del->name);
		ft_free_ptr((void *) &del);
	}
}

void	ms_go_start(t_file **files)
{
	while ((*files)->prev != NULL)
		*files = (*files)->prev;
}

int	valid_chr(char chr)
{
	if (chr != '\'' && chr != '\"' \
		&& chr != '\0' && chr != ' ')
		return (1);
	return (0);
}
