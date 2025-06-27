/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darray_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:01:59 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 14:02:10 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_darray_free(char **darray)
{
	int	i;

	i = 0;
	if (!darray)
		return ;
	while (darray[i])
	{
		free(darray[i]);
		i++;
	}
	free(darray);
}
