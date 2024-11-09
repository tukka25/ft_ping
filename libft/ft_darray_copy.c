#include "libft.h"

char **ft_darray_copy(char **src)
{
	int i;
	char **ret;

	i = 0;
	if (!src)
		return NULL;
	// printf("s = %s\n", src[0]);
	ret = malloc((ft_darray_len(src) + 1) * sizeof(char *));
	while (src[i])
	{
		ret[i] = ft_strdup(src[i]);
		i++;
	}
	ret[i] = NULL;
	return ret;
}