/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darray_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:02:17 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 14:02:27 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_darray_len(char **src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
		i++;
	return (i);
}
