/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darray_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:01:41 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 14:02:31 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_darray_copy(char **src)
{
	int		i;
	char	**ret;

	i = 0;
	if (!src)
		return (NULL);
	ret = malloc((ft_darray_len(src) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (src[i])
	{
		ret[i] = ft_strdup(src[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
