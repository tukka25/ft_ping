/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:26:56 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 12:10:12 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short	calculate_checksum(unsigned short *icmp, int len)
{
	int			sum;
	u_short		*tmp_icmp;
	uint16_t	final;

	sum = 0;
	tmp_icmp = icmp;
	final = 0;
	while (len > 1)
	{
		sum += *tmp_icmp++;
		len -= 2;
	}
	if (len != 0)
		sum += *(uint8_t *)tmp_icmp;
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	final = ~sum;
	return (final);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_is_running = 0;
}

void	add_timing(float g, t_ping *ping)
{
	ping->timings = realloc(ping->timings,
			(ping->index * (size_t) sizeof(float))
			+ (size_t) sizeof(float));
	ping->timings[ping->index] = g;
	ping->index++;
}

void	packet_failure(t_ping *ping, char *msg)
{
	free(ping->buffer);
	free(ping->packet);
	error_handle(EXIT_FAILURE, msg, ping);
}

void	ip_icmp_initialization(struct iphdr *ip, struct icmphdr *icmp,
		t_ping *ping, size_t packet_size)
{
	ip->version = 4;
	ip->tot_len = packet_size;
	ip->ttl = 64;
	ip->protocol = IPPROTO_ICMP;
	ip->daddr = inet_addr(ping->ip_rep);
	ip->ihl = 5;
	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = getpid();
	icmp->un.echo.sequence = htons(1);
	icmp->checksum = calculate_checksum((unsigned short *)icmp,
			sizeof(struct icmphdr));
}
