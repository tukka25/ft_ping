#include "ft_ping.h"

int is_running = 1;

unsigned short calculate_checksum(unsigned short *icmp, int len)
{
	int sum = 0;
	u_short *tmp_icmp = icmp; // int16
	uint16_t final = 0;
	
	while (len > 1)
	{
		sum += *tmp_icmp++;
		len -= 2;
	}
	if (len != 0)
		sum += *(uint8_t *)tmp_icmp;
	// 32-bit sum is folded into 16 bits using an end-around carry method
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	final = ~sum;
	return final;
}



void handle_sigint(int sig)
{ 
	(void)sig;
	is_running = 0;
}

void add_timing(float g, t_ping *ping)
{
	ping->timings = realloc(ping->timings, (ping->index * (size_t)sizeof(float)) + (size_t)sizeof(float));
	ping->timings[ping->index] = g;
	ping->index++;
}

// void iphdr_config(struct iphdr* packet)
// {

// }

// void icmp_config()

void packet_send(t_ping *ping)
{
	// PF_PACKET is a raw socket works in linux
	/* IPPROTO_RAW is a protocol for raw socket to get and receive
	instead od IPPROTO_IP that only send */
	struct icmphdr* icmp;
	struct iphdr* ip_reply;
	struct iphdr* ip;
	struct sockaddr_in sockadd;
	char *packet;
	struct timeval timeout;
	char *buffer;

	// ip = malloc(sizeof(struct iphdr));
	// if (!ip)
	// 	error_handle(EXIT_FAILURE, "Error: Failed to allocate memory for ip", ping);
	// icmp = malloc(sizeof(struct icmphdr));
	// if (!icmp)
	// 	error_handle(EXIT_FAILURE, "Error: Failed to allocate memory for icmp", ping);
	packet = calloc(1, sizeof(struct iphdr) + sizeof(struct icmphdr));
	if (!packet)
		error_handle(EXIT_FAILURE, "Error: Failed to allocate memory for packet", ping);
	buffer = calloc(1, (sizeof(struct iphdr) + sizeof(struct icmphdr)) + 1);
	if (!buffer)
		error_handle(EXIT_FAILURE, "Error: Failed to allocate memory for buffer", ping);
	ip = (struct iphdr*)packet;
	icmp = (struct icmphdr*)(packet + sizeof(struct iphdr));

	/* IP conf */
	struct timeval stop, start;
	ip->version          = 4;
	ip->tot_len          = sizeof(struct iphdr) + sizeof(struct icmphdr); // 20 + 8 = 28
	ip->ttl          	= 64; // to be set
	ip->protocol     = IPPROTO_ICMP;
    ip->daddr            = inet_addr(convert_domain_to_ip(ping->dest_ip, ping));
	ip->ihl 		= 5; // if we want to put extra headers like options or timestamp we should increase it. for now ==> 5 * 4

	/** ICMP conf **/
	icmp->type           = ICMP_ECHO;
    icmp->code           = 0; // code 0 for echo request
    icmp->un.echo.id     = getpid();
    icmp->un.echo.sequence   = htons(1);
	icmp->checksum = calculate_checksum((unsigned short*)icmp, sizeof(struct icmphdr));

	sockadd.sin_family = AF_INET;
	sockadd.sin_port = 0;
	sockadd.sin_addr.s_addr = inet_addr(convert_domain_to_ip(ping->dest_ip, ping));
	int sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		printf("Error file\n");
		exit(1);
	}
	printf("Socket created Successfully\n");
	int yes = 1;

	timeout.tv_sec = TIMEOUT;
	timeout.tv_usec = 0;
	int sockOpt = setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(yes));
	if (sockOpt < 0)
	{
		printf("Error setsockopt\n");
		exit(1);
	}
	if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
                sizeof timeout) < 0)
        herror("setsockopt failed\n");
	int seq = 1;
	signal(SIGINT, handle_sigint);
	while (is_running)
	{
		gettimeofday(&start, NULL);
		int sendt = sendto(sockfd, packet, ip->tot_len, 0, (struct sockaddr *)&sockadd, sizeof(struct sockaddr));
		if (sendt < 0)
		{
			printf("sendto() failed! Error: %s (errno: %d)\n", strerror(errno), errno);
			exit(1);
		}
		else
		{
			ping->transmitted_packets += 1;
			int addr_len = sizeof(sockadd);
			int recv_f = recvfrom(sockfd, buffer, (sizeof(struct iphdr) + sizeof(struct icmphdr)), 0, (struct sockaddr *)&sockadd, (unsigned int * restrict)&addr_len);
			ip_reply = (struct iphdr*) buffer;
			gettimeofday(&stop, NULL);
			if (recv_f < 0)
			{
				printf("Timeout!!!: The request exceeded 4 sec\n");
			}
			else
			{
				float elapsed_time = (((stop.tv_sec * 1000) + (stop.tv_usec / 1000)) - ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
				ping->recieved_packets += 1;
				printf("%d bytes from %s: icmp seq=%d ttl=%d time=%.1lf\n",  recv_f, ping->dest_ip, seq, ip_reply->ttl, elapsed_time);
				add_timing(elapsed_time, ping);
			}
			usleep(900000);
			
		}
		seq++;
		icmp->un.echo.sequence = htons(seq);
		icmp->checksum = 0;
		icmp->checksum = calculate_checksum((unsigned short*)icmp, sizeof(struct icmphdr));
	}
	int h = 1000;
	float loss_p = 100.0 - (((float)ping->recieved_packets / ping->transmitted_packets) * 100.0);

	printf("\n--- %s ft_ping statistics ---\n", ping->dest_ip);
	printf("%d packets transmitted, %d received, %0.4f%% packet loss, time %d\n", ping->transmitted_packets, ping->recieved_packets, loss_p, h);
	printf("rtt min/avg/max/mdev = %f/%f/%f/%f ms\n", get_minimum(ping), get_average(ping),get_maximum(ping), get_minimum(ping));
	free(ping->timings);
	// free(ip);
	// free(icmp);
	free(buffer);
	free(packet);
	close(sockfd);
	error_handle(EXIT_SUCCESS, "", ping);
	// free(ip);
}