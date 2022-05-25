
#include <libft.h>

int		ft_str_indexof(char *big, char *little, size_t n)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	j = 0;
	k = 0;
	i = ft_strlen(little);
	if (i == 0)
		return (0);
	if (n == 0)
		return (-1);
	while (big[j] && (j + i - 1) < n)
	{
		while (little[k] == big[j + k])
		{
			if ((k + 1) == i)
				return (j);
			k++;
		}
		k = 0;
		j++;
	}
	return (-1);
}
