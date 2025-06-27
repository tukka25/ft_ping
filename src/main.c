/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:27:01 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 12:07:43 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	main(int ac, char **av)
{
	t_ping	ping;

	if (ac >= 2 && ac <= 3)
	{
		setup(&ping);
		input_parsing(av, &ping);
		packet_send(&ping);
		return (0);
	}
	print_usage();
	return (1);
}
