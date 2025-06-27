/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:46:12 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 12:26:53 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

/*
This function sets up the environment to run the program.
*/
void	setup(t_ping *ping)
{
	char	*s[FLAG_OPTIONS_NUMBER + 1];

	s[0] = "-v";
	s[1] = "-?";
	s[2] = NULL;
	ft_bzero(ping, sizeof(t_ping));
	ping->yes = 1;
	ping->flags_options = ft_darray_copy(s);
	if (!ping->flags_options)
		error_handle(EXIT_FAILURE, "Error: Failed to copy flags options", ping);
}

/*
This function prints the usage of the program
*/
void	print_usage(void)
{
	printf("Usage:\n");
	printf("  ./ft_ping [FLAG] [IP/DOMAIN]\n\n");
	printf("Flags:\n");
	printf("  -v ===> Verbose mode\n\n");
	printf("  -? ===> Help\n\n");
	printf("IP Format:\n");
	printf("  xxx.xxx.xxx.xxx\n");
	printf("DOMAIN Format:\n");
	printf("  www.example.com\n");
}

/*
The function prints %msg in %fd and exits incase of an error occurred.
*/
void	error_handle(int status, char *msg, t_ping *ping)
{
	if (!msg)
		exit(EXIT_FAILURE);
	if (status == EXIT_FAILURE)
		fprintf(stderr, "%s\n", msg);
	ft_darray_free(ping->flags_options);
	free(ping->flag);
	free(ping->dest_ip);
	exit(status);
}

float	get_minimum(t_ping *ping)
{
	float	min;
	int		i;

	i = 1;
	if (!ping->timings || ping->index == 0)
		return (0);
	min = ping->timings[0];
	while (i < ping->index)
	{
		if (ping->timings[i] < min)
			min = ping->timings[i];
		i++;
	}
	return (min);
}

float	get_average(t_ping *ping)
{
	float	avg;
	int		i;

	i = 0;
	avg = 0;
	while (i < ping->index)
	{
		avg += ping->timings[i];
		i++;
	}
	if (avg == 0)
		return (0);
	return (avg / ping->index);
}
