/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:26:53 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 12:23:50 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int			g_is_running = 1;

int	create_socket(t_ping *ping)
{
	int	sockfd;

	ping->sockadd.sin_family = AF_INET;
	ping->sockadd.sin_port = 0;
	ping->sockadd.sin_addr.s_addr = inet_addr(ping->ip_rep);
	sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
		packet_failure(ping, "Error: Failed to create raw socket");
	return (sockfd);
}

void	next_ping_setup(t_ping *ping)
{
	usleep(1000000);
	ping->seq++;
	ping->icmp->un.echo.sequence = htons(ping->seq);
	ping->icmp->checksum = 0;
	ping->icmp->checksum = calculate_checksum((unsigned short *)ping->icmp,
			sizeof(struct icmphdr));
}

static void	init_packet_send(t_ping *ping, t_packet *packet)
{
	init_packet_memory(ping);
	ip_icmp_initialization(ping->ip, ping->icmp, ping, ping->packet_size);
	ping->sockfd = create_socket(ping);
	flag_options_printing(ping);
	setting_options(ping);
	signal(SIGINT, handle_sigint);
	gettimeofday(&packet->start_total, NULL);
}

static void	handle_send(t_ping *ping, t_packet *packet)
{
	ping->transmitted_packets += 1;
	ping->addr_len = sizeof(ping->sockadd);
	ping->recv_f = recvfrom(ping->sockfd, ping->buffer, ping->packet_size, 0,
			(struct sockaddr *)&ping->sockadd,
			(unsigned int *restrict) & ping->addr_len);
	ping->ip_reply = (struct iphdr *)ping->buffer;
	ping->icmp_reply = (struct icmphdr *)(ping->buffer + sizeof(struct iphdr));
	gettimeofday(&packet->stop, NULL);
	if (ping->recv_f > 0)
	{
		ping->elapsed_time = (((packet->stop.tv_sec * 1000)
					+ (packet->stop.tv_usec / 1000)) - ((packet->start.tv_sec
						* 1000) + (packet->start.tv_usec / 1000)));
		ping->recieved_packets += 1;
		packet_reply_printing(ping->icmp_reply->type, ping->recv_f,
			ping->elapsed_time, ping);
	}
}

void	packet_send(t_ping *ping)
{
	t_packet	packet;

	init_packet_send(ping, &packet);
	while (g_is_running)
	{
		gettimeofday(&packet.start, NULL);
		ping->sendt = sendto(ping->sockfd, ping->packet, ping->packet_size, 0,
				(struct sockaddr *)&ping->sockadd, sizeof(struct sockaddr));
		if (ping->sendt > 0)
			handle_send(ping, &packet);
		next_ping_setup(ping);
	}
	gettimeofday(&packet.stop_total, NULL);
	final_printing_exit(&packet.stop, &packet.start, ping, ping->sockfd);
}
