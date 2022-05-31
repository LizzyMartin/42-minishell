#include <libft.h>

char	**ft_mtx_dup(char **duped_mtx)
{
	int		i;
	char	**matrix;
	int		width;
	int		height;

	if (duped_mtx == NULL)
		return (NULL);
	matrix = NULL;
	width = 0;
	height = 0;
	width = ft_strlen(duped_mtx[0]);
	while (duped_mtx[height])
		height++;
	i = -1;
	matrix = (char **) ft_calloc (height + 1, sizeof(char *));
	while (++i < height)
		matrix[i] = ft_strdup(duped_mtx[i]);
	return (matrix);
}
