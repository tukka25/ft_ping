#ifndef FT_PING_H
# define FT_PING_H


#include <stdio.h>
#include <sys/time.h>
#include<signal.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include "./libft/libft.h"

# define FLAG_OPTIONS_NUMBER 1
# define MAX_FLAG_SIZE 14
# define TIMEOUT 4

extern int is_running;

#define SIGINT  2   /* Interrupt the process */ 
#define SIGQUIT 3   /* Quit the process */ 

typedef struct s_ping
{
	char	**flags_options;
	char	*dest_ip;
	float	*timings;
	int		index;
	char	*flag;
	int		transmitted_packets;
	int		recieved_packets;
}	t_ping;


void	error_handle(int fd, char *msg);
float	get_minimum(t_ping *ping);
float	get_maximum(t_ping *ping);
float	get_average(t_ping *ping);
void	setup(t_ping *ping);
void	input_parsing(char **av, t_ping *ping);
void	print_usage();
int		flag_validation(char **av, t_ping *ping);
int		ip_validation(char **av, t_ping *ping);
void	packet_send(t_ping *ping);

#endif