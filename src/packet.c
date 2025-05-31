#include "ft_ping.h"

int is_running = 1;


void final_printing_exit(struct timeval *stop, struct timeval *start, t_ping *ping, int sockfd)
{
	int total_time = (((stop->tv_sec * 1000) + (stop->tv_usec / 1000)) - ((start->tv_sec * 1000) + (start->tv_usec / 1000)));
	float loss_p = 100.0 - (((float)ping->recieved_packets / ping->transmitted_packets) * 100.0);

	printf("\n--- %s ft_ping statistics ---\n", ping->dest_ip);
	printf("%d packets transmitted, %d received, %0.4f%% packet loss, time %d ms\n", ping->transmitted_packets, ping->recieved_packets, loss_p, total_time);
	printf("rtt min/avg/max/mdev = %f/%f/%f/%f ms\n", get_minimum(ping), get_average(ping),get_maximum(ping), get_mdev(ping));
	free(ping->timings);
	free(ping->buffer);
	free(ping->packet);
	close(sockfd);
	error_handle(EXIT_SUCCESS, "", ping);
}

void init_packet_memory(t_ping *ping, size_t packet_size)
{
	ping->packet_size = sizeof(struct iphdr) + sizeof(struct icmphdr) + 56;
	ping->packet = ft_calloc(1, ping->packet_size + 1);
	if (!ping->packet)
		packet_failure(ping, "Error: Failed to allocate memory for packet");
	ping->buffer = ft_calloc(1, ping->packet_size + 1);
	if (!ping->buffer)
		packet_failure(ping, "Error: Failed to allocate memory for buffer");
	ip = (struct iphdr*)ping->packet;
	icmp = (struct icmphdr*)(ping->packet + sizeof(struct iphdr));
	ping->ip_rep = convert_domain_to_ip(ping->dest_ip, ping);
}

void packet_send(t_ping *ping)
{
	struct icmphdr* icmp;
	struct iphdr* ip_reply;
	struct iphdr* ip;
	struct timeval timeout;

	init_packet_memory(ping, ping->packet_size);
	struct timeval stop, start;
	struct timeval stop_total, start_total;

	ip_icmp_initialization(ip, icmp, ping, ping->packet_size);

	ping->sockadd.sin_family = AF_INET;
	ping->sockadd.sin_port = 0;
	ping->sockadd.sin_addr.s_addr = inet_addr(ping->ip_rep);
	int sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
		packet_failure(ping, "Error: Failed to create raw socket");

	flag_options_printing(ping, icmp->un.echo.id);

	timeout.tv_sec = TIMEOUT;
	timeout.tv_usec = 0;
	int sockOpt = setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &ping->yes, sizeof(ping->yes));
	if (sockOpt < 0)
	{
		printf("Error setsockopt\n");
		packet_failure(ping, "Error: Failed to set socket options");
	}
	if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
                sizeof timeout) < 0)
        packet_failure(ping, "Error: Failed to set socket options");
	int seq = 0;
	signal(SIGINT, handle_sigint);
	gettimeofday(&start_total, NULL);
	while (is_running)
	{
		gettimeofday(&start, NULL);
		int sendt = sendto(sockfd, ping->packet, ping->packet_size, 0, (struct sockaddr *)&ping->sockadd, sizeof(struct sockaddr));

		if (sendt > 0)
		{
			ping->transmitted_packets += 1;
			int addr_len = sizeof(ping->sockadd);
			int recv_f = recvfrom(sockfd, ping->buffer, ping->packet_size, 0, (struct sockaddr *)&ping->sockadd, (unsigned int * restrict)&addr_len);
			ip_reply = (struct iphdr*) ping->buffer;
			struct icmphdr *icmp_reply = (struct icmphdr *)(ping->buffer + sizeof(struct iphdr));
			gettimeofday(&stop, NULL);
			if (recv_f > 0)
			{
				float elapsed_time = (((stop.tv_sec * 1000) + (stop.tv_usec / 1000)) - ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
				ping->recieved_packets += 1;
				packet_reply_printing(icmp_reply->type, recv_f, ip_reply, seq, elapsed_time, ping);
			}
		}
		usleep(1000000);
		seq++;
		icmp->un.echo.sequence = htons(seq);
		icmp->checksum = 0;
		icmp->checksum = calculate_checksum((unsigned short*)icmp, sizeof(struct icmphdr));
	}
	gettimeofday(&stop_total, NULL);
	final_printing_exit(&stop, &start, ping, sockfd);
<<<<<<< HEAD
=======
}

void final_printing_exit(struct timeval *stop, struct timeval *start, t_ping *ping, int sockfd)
{
	int total_time = (((stop->tv_sec * 1000) + (stop->tv_usec / 1000)) - ((start->tv_sec * 1000) + (start->tv_usec / 1000)));
	float loss_p = 100.0 - (((float)ping->recieved_packets / ping->transmitted_packets) * 100.0);

	printf("\n--- %s ft_ping statistics ---\n", ping->dest_ip);
	printf("%d packets transmitted, %d received, %0.4f%% packet loss, time %d ms\n", ping->transmitted_packets, ping->recieved_packets, loss_p, total_time);
	printf("rtt min/avg/max/mdev = %f/%f/%f/%f ms\n", get_minimum(ping), get_average(ping),get_maximum(ping), get_mdev(ping));
	free(ping->timings);
	free(ping->buffer);
	free(ping->packet);
	close(sockfd);
	error_handle(EXIT_SUCCESS, "", ping);
>>>>>>> bdf1fc2f05e8afe5bb6e405f206de0274fff276f
}