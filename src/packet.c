#include "ft_ping.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>


unsigned short calculate_checksum(unsigned short *icmp, int len)
{
	int sum = 0;
	u_short *tmp_icmp = icmp; // int16
	uint16_t final = 0;
	
	printf("len = %d\n", len);
	while (len > 1)
	{
		sum += *tmp_icmp++;
		printf("sum in loop = %d\n" , sum);
		printf("tmp_icmp in loop= %hu\n", *tmp_icmp);
		len -= 2;
		printf("len in loop= %d\n", len);
	}
	if (len != 0)
	{
		sum += *(uint8_t *)tmp_icmp;
	}
	printf("sum after norm = %d\n", sum);
	// 32-bit sum is folded into 16 bits using an end-around carry method
	while (sum >> 16)
	{
		printf("sum bef summing = %d\n", sum);
		sum = (sum & 0xffff) + (sum >> 16);
		printf("sum in summing = %d\n", sum);
	}
	printf("sum after getting least = %d\n", sum);
	final = ~sum;
	// printf("sum after = %d\n", final);
	return final;
}

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
	char *buffer;


	printf("Started...\n");
	ip = malloc(sizeof(struct iphdr));
	icmp = malloc(sizeof(struct icmphdr));
	packet = malloc(sizeof(struct iphdr) + sizeof(struct icmphdr));
	buffer = malloc((sizeof(struct iphdr) + sizeof(struct icmphdr)) + 1);

	ip = (struct iphdr*)packet;
	printf("Size of iphdr: %ld\n", sizeof(struct iphdr));
	icmp = (struct icmphdr*) (packet + sizeof(struct iphdr));
	printf("icmp size: %ld\n", sizeof(struct icmp));
	/* ip conf */
	ip->version          = 4;
	ip->tot_len          = sizeof(struct iphdr) + sizeof(struct icmphdr); // 20 + 8 = 28
	ip->ttl          	= 0; // to be set
	ip->protocol     = IPPROTO_ICMP;
	ip->ihl 		= 5; // if we want to put extra headers like options or timestamp we should increase it. for now ==> 5 * 4
	/** ICMP conf **/
	icmp->type           = ICMP_ECHO;
    icmp->code           = 0; // code 0 for echo request
    icmp->un.echo.id     = random();
    icmp->un.echo.sequence   = 0;
	icmp->checksum = calculate_checksum((unsigned short*)icmp, sizeof(struct icmphdr));

	sockadd.sin_family = AF_INET;
	printf("dest_ip = %s\n", ping->dest_ip);
	sockadd.sin_addr.s_addr = inet_addr(ping->dest_ip);

	// int addrinfo = getaddrinfo(const char *hostname, const char *servname, const struct addrinfo *hints, struct addrinfo **res);
	int sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		printf("Error file\n");
		exit(1);
	}
	printf("Socket created Successfully\n");
	int yes = 1;

	int sockOpt = setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(yes));
	if (sockOpt < 0)
	{
		printf("Error setsockopt\n");
		exit(1);
	}
	int k = 64;
	int i = 0;
	// while (i < k)
	// {
		int sendt = sendto(sockfd, packet, ip->tot_len, 0, (struct sockaddr *)&sockadd, sizeof(struct sockaddr));
		if (sendt < 0)
		{
			
			printf("send ret = %d\n", sendt);
			// continue;

		}
		else
		{
			printf("INNN\n");
			int addr_len = sizeof(sockadd);
			int recv_f = recvfrom(sockfd, buffer, (sizeof(struct iphdr) + sizeof(struct icmphdr)), 0, (struct sockaddr *)&sockadd, &addr_len);
			ip_reply = (struct iphdr*) buffer;
			printf("ID: %d\n", ntohs(ip_reply->id));
    		printf("TTL: %d\n", ip_reply->ttl);
			// printf("recv_f = %d\n", recv_f);
			// printf("recv_f = %d\n", recv_f);
			// printf("recv_f = %d\n", recv_f);
			// printf("recv_f = %d\n", recv_f);
			// printf("recv_f = %d\n", recv_f);
			if (recv_f < 0)
			{
				printf("less than\n");
				// ip->ttl = i + 1;
			}
			else
			{
				printf("Received %d byte reply from %s:\n",  recv_f, ping->dest_ip);
			}
			printf("reached Successfully\n");
		}
		
		// printf("ret of send to = %d\n", sendt);
		// printf("Sent %d byte packet to %s\n", ip->tot_len, ping->dest_ip);
		// i++;
	// }
	// send through sendto
	// int sendto_ret = sendto(sockfd, )
	
}