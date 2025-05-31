/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:59:35 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 14:03:35 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ispart(char **darray, char *str)
{
	int	i;

	i = 0;
	if (!darray || !str)
		return (1);
	while (darray[i])
	{
		if (strcmp(darray[i], str) == 0)
			return (0);
		i++;
	}
	return (1);
}
