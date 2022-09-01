/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:53:50 by acapela-          #+#    #+#             */
/*   Updated: 2022/09/01 16:37:48 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_aste(char **wc_split, int i, char *wc, t_file *head)
{
	int		len;
	char	*after_aste;

	after_aste = NULL;
	after_aste = head->name + head->cursor;
	len = ft_mtx_size((void **) wc_split);
	if (i == 0 && wc[0] != '*' && ft_strncmp(wc_split[0],
			head->name, ft_strlen(wc_split[0])) != 0)
		return (1);
	else if (i == (len - 1) && wc[0] == '*' && ft_rev_strncmp(head->name,
			wc_split[i], ft_strlen(wc_split[i])) != 0)
		return (1);
	else if (i == (len - 1) && wc[ft_strlen(wc) - 1] != '*'
		&& ft_rev_strncmp(head->name, wc_split[i], ft_strlen(wc_split[i])) != 0)
		return (1);
	else if (len > 2 && ft_strnstr(after_aste, wc_split[i],
			ft_strlen(head->name)) == NULL)
		return (1);
	return (0);
}

static int	ms_file_match_wc2(int *z, char **wc_split, t_file **head, int i)
{
	int		nlen;
	int		wcsplitlen;

	wcsplitlen = ft_strlen(wc_split[i]);
	nlen = ft_strlen((*head)->name);
	(*head)->cursor = ft_str_indexof((*head)->name,
			wc_split[i], nlen) + wcsplitlen;
	(*head) = (*head)->next;
	(void) z;
	return (*z + 1);
}

static int	ms_file_match_wc(char *wc, t_file **files)
{
	int		i;
	t_file	*head;
	char	**wc_split;
	int		z;
	int		len;

	i = -1;
	wc_split = ft_split(wc, '*');
	head = (*files);
	len = ft_mtx_size((void **) wc_split);
	while (++i < len)
	{
		z = 0;
		while (head->next != NULL)
			if (check_aste(wc_split, i, wc, head))
				ms_file_delete(&head);
		else
			z = ms_file_match_wc2(&z, wc_split, &head, i);
		ms_go_start(&head);
	}
	(*files) = head;
	ft_mtx_free((void **) wc_split);
	if (z == 0)
		return (0);
	return (1);
}

static char	*ms_find_wc_files(char *wc, t_file **files)
{
	char	*wc_files;
	char	*tmp;

	tmp = NULL;
	wc_files = ft_strdup("");
	if (ft_strncmp(wc, "*", ft_strlen(wc)) != 0
		&& ms_file_match_wc(wc, files) == 0)
		return (ft_strdup(wc));
	else
	{
		while ((*files) != NULL && (*files)->name != NULL)
		{
			tmp = ft_strdup(wc_files);
			ft_free_ptr((void *) &wc_files);
			wc_files = ft_printf_to_var("%s%s ", tmp, (*files)->name);
			(*files) = (*files)->next;
			ft_free_ptr((void *) &(*files)->prev->name);
			ft_free_ptr((void *) &(*files)->prev);
			free(tmp);
		}
	}
	ft_free_ptr((void *) &(*files)->name);
	ft_free_ptr((void *) &(*files));
	return (wc_files);
}

void	ms_wildcard(t_ms *ms)
{
	t_file	*files;
	char	**args;
	int		i;
	char	*wc_files;
	char	*tmp;

	i = 0;
	files = NULL;
	args = ft_split(ms->shell_line_tokenized, ' ');
	files = ms_get_current_directory();
	while (args[i])
	{
		if (ft_strnstr(args[i], "*", ft_strlen(args[i])))
		{
			wc_files = ms_find_wc_files(args[i], &files);
			tmp = ft_strdup(ms->shell_line_tokenized);
			ft_free_ptr((void *) &ms->shell_line_tokenized);
			ms->shell_line_tokenized = ft_str_replace(tmp,
					args[i], wc_files);
			ft_free_ptr((void *) &wc_files);
		}
		i++;
	}
	ft_mtx_free((void **) args);
}
