/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- < acapela-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:44:12 by acapela-          #+#    #+#             */
/*   Updated: 2021/09/20 12:21:19 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<libft.h>

static int	ft_countwords(char *str, char *token)
{
	char	*tmp;
	int		w;

	w = 0;
	tmp = ft_strdup(str);
	while (*tmp)
	{
	 	if (ft_strnstr(tmp, token, ft_strlen(token)))
	 		w++;
	 	tmp++;
	}
	return (w);
}

static int	ft_wordlen(char *str, char *token)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = ft_strdup(str);
	while (*tmp)
	{
	 	if (ft_strnstr(tmp, token, ft_strlen(token)) == NULL)
	 		len++;
		else
			return (len);
	 	tmp++;
	}
	return (len);
}

char	**ft_tosplit(char *s, char *token, char **split)
{
	char *tmp;
	int	i;
	int	j;

	j = 0;
	i = 0;
	tmp = ft_strdup(s);
	while (*tmp)
	{
		if (ft_strnstr(tmp, token, ft_strlen(token)))
		{
			split[j] = (char *) malloc((i) * sizeof(char));
			if (split[j] != NULL)
				ft_strlcpy (split[j], s, ft_wordlen(s, token) + 1);
			tmp += ft_strlen(token);
			s = ft_strdup(tmp);
			j++;
		}
		i++;
		tmp++;
	}
	split[j] = (char *) malloc((i) * sizeof(char));
	ft_strlcpy (split[j], s, ft_strlen(s) + 1);
	return (split);
}

char	**ft_split_by_str(char *s, char *token)
{
	char	**split;
	int		words;

	if (!s)
		return (0);
	words = ft_countwords(s, token);
	words++;
	split = (char **) malloc ((words + 1) * sizeof(char **));
	if (!split)
		return (NULL);
	split = ft_tosplit(s, token, split);
	split[words] = NULL;
	return (split);
}
