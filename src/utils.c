/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:26:35 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 12:04:46 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

float	get_maximum(t_ping *ping)
{
	float	max;
	int		i;

	i = 1;
	if (!ping->timings || ping->index == 0)
		return (0);
	max = ping->timings[0];
	while (i < ping->index)
	{
		if (ping->timings[i] > max)
			max = ping->timings[i];
		i++;
	}
	return (max);
}

float	get_mdev(t_ping *ping)
{
	float	mdev;
	int		i;

	i = 0;
	mdev = 0;
	while (i < ping->index)
	{
		mdev += fabs(ping->timings[i] - get_average(ping));
		i++;
	}
	if (mdev == 0)
		return (0);
	return (mdev / ping->index);
}

char	*convert_domain_to_ip(char *domain, t_ping *ping)
{
	struct hostent	*h;
	char			error_msg[256];

	h = gethostbyname(domain);
	if (!h)
	{
		snprintf(error_msg,
			sizeof(error_msg),
			"ft_ping: \
			%s: Temporary failure in name resolution",
			domain);
		packet_failure(ping, error_msg);
	}
	return (inet_ntoa(*(struct in_addr *)h->h_addr));
}

void	flag_options_printing(t_ping *ping)
{
	if (ping->flag)
	{
		if (strcmp(ping->flag, "-v") == 0)
		{
			fprintf(stdout, "\nPING %s (%s): 56 data bytes, id 0x%x = %d\n",
				ping->dest_ip, ping->ip_rep, ping->icmp->un.echo.id,
				ping->icmp->un.echo.id);
		}
	}
}

void	packet_reply_printing(int type, int recv_f, float elapsed_time,
		t_ping *ping)
{
	struct in_addr	src_addr;

	src_addr.s_addr = ping->ip_reply->saddr;
	if (type == 3)
		printf("Destination Unreachable\n");
	else if (type == 5)
		printf("Redirect\n");
	else if (type == 11)
		printf("%ld bytes from %s: Time to live exceeded\n", recv_f
			- sizeof(struct iphdr), inet_ntoa(src_addr));
	else if (type == 12)
		printf("Parameter Problem\n");
	else
		printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms\n", recv_f
			- sizeof(struct iphdr), inet_ntoa(src_addr), ping->seq,
			ping->ip_reply->ttl, elapsed_time);
	add_timing(elapsed_time, ping);
}
