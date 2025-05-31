/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:48:24 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 12:27:36 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	final_printing_exit(struct timeval *stop, struct timeval *start,
		t_ping *ping, int sockfd)
{
	int		total_time;
	float	loss_p;

	total_time = (((stop->tv_sec * 1000) + (stop->tv_usec / 1000))
			- ((start->tv_sec * 1000) + (start->tv_usec / 1000)));
	loss_p = 100.0 - (((float)ping->recieved_packets
				/ ping->transmitted_packets) * 100.0);
	printf("\n--- %s ft_ping statistics ---\n", ping->dest_ip);
	printf("%d packets transmitted, %d received, %0.4f%% packet loss, time "
		"%d ms\n", ping->transmitted_packets, ping->recieved_packets, loss_p,
		total_time);
	printf("rtt min/avg/max/mdev = %f/%f/%f/%f ms\n", get_minimum(ping),
		get_average(ping), get_maximum(ping), get_mdev(ping));
	free(ping->timings);
	free(ping->buffer);
	free(ping->packet);
	close(sockfd);
	error_handle(EXIT_SUCCESS, "", ping);
}

void	init_packet_memory(t_ping *ping)
{
	ping->packet_size = sizeof(struct iphdr) + sizeof(struct icmphdr) + 56;
	ping->packet = ft_calloc(1, ping->packet_size + 1);
	if (!ping->packet)
		packet_failure(ping, "Error: Failed to allocate memory for packet");
	ping->buffer = ft_calloc(1, ping->packet_size + 1);
	if (!ping->buffer)
		packet_failure(ping, "Error: Failed to allocate memory for buffer");
	ping->ip = (struct iphdr *)ping->packet;
	ping->icmp = (struct icmphdr *)(ping->packet + sizeof(struct iphdr));
	ping->ip_rep = convert_domain_to_ip(ping->dest_ip, ping);
}

void	setting_options(t_ping *ping)
{
	struct timeval	timeout;
	int				sockopt;

	timeout.tv_sec = TIMEOUT;
	timeout.tv_usec = 0;
	sockopt = setsockopt(ping->sockfd, IPPROTO_IP, IP_HDRINCL, &ping->yes,
			sizeof(ping->yes));
	if (sockopt < 0)
	{
		printf("Error setsockopt\n");
		packet_failure(ping, "Error: Failed to set socket options");
	}
	if (setsockopt(ping->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
			sizeof timeout) < 0)
		packet_failure(ping, "Error: Failed to set socket options");
}
