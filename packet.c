#include "ft_ping.h"

void packet_send(t_ping *ping)
{
	int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sockfd < 0)
	{
		printf("Error file\n");
		exit(1);
	}
}