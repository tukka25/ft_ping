#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pcap.h>
// #include <linux/if_packet.h>
#include <net/ethernet.h>
#include "./libft/libft.h"

# define FLAG_OPTIONS_NUMBER 1
# define MAX_FLAG_SIZE 14


typedef struct s_ping
{
	char	**flags_options;
	char	*ip;
	char	*flag;
}	t_ping;


void error_handle(int fd, char *msg);
void setup(t_ping *ping);
void input_parsing(char **av, t_ping *ping);
void print_usage();
int flag_validation(char **av, t_ping *ping);
int ip_validation(char **av, t_ping *ping);
void packet_send(t_ping *ping);

#endif