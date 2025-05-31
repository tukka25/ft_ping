/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha42 <abdamoha42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:27:04 by abdamoha42        #+#    #+#             */
/*   Updated: 2025/05/31 12:29:05 by abdamoha42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "./libft/libft.h"
# include <arpa/inet.h>
# include <errno.h>
# include <math.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/in_systm.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define FLAG_OPTIONS_NUMBER 2
# define MAX_FLAG_SIZE 14
# define TIMEOUT 4

extern int				g_is_running;

# define SIGINT 2 /* Interrupt the process */
# define SIGQUIT 3 /* Quit the process */

typedef struct s_packet
{
	struct timeval	stop;
	struct timeval	start;
	struct timeval	stop_total;
	struct timeval	start_total;
}	t_packet;

typedef struct s_ping
{
	char				**flags_options;
	char				*dest_ip;
	char				*ip_rep;
	char				*packet;
	int					sockfd;
	int					seq;
	int					sendt;
	int					addr_len;
	int					recv_f;
	struct icmphdr		*icmp_reply;
	float				elapsed_time;
	struct icmphdr		*icmp;
	struct iphdr		*ip_reply;
	struct iphdr		*ip;
	struct sockaddr_in	sockadd;
	size_t				packet_size;
	char				*buffer;
	float				*timings;
	int					index;
	int					yes;
	char				*flag;
	int					transmitted_packets;
	int					recieved_packets;
}						t_ping;

void					error_handle(int status, char *msg, t_ping *ping);
float					get_minimum(t_ping *ping);
void					packet_failure(t_ping *ping, char *msg);
float					get_maximum(t_ping *ping);
float					get_average(t_ping *ping);
void					setup(t_ping *ping);
void					input_parsing(char **av, t_ping *ping);
void					print_usage(void);
int						flag_validation(char **av, t_ping *ping);
int						ip_validation(char **av, t_ping *ping);
void					packet_send(t_ping *ping);
char					*convert_domain_to_ip(char *domain, t_ping *ping);
float					get_mdev(t_ping *ping);
void					flag_options_printing(t_ping *ping);
void					packet_reply_printing(int type, int recv_f,
							float elapsed_time, t_ping *ping);
void					add_timing(float g, t_ping *ping);
void					final_printing_exit(struct timeval *stop,
							struct timeval *start, t_ping *ping, int sockfd);
void					ip_icmp_initialization(struct iphdr *ip,
							struct icmphdr *icmp, t_ping *ping,
							size_t packet_size);
void					packet_failure(t_ping *ping, char *msg);
void					add_timing(float g, t_ping *ping);
void					handle_sigint(int sig);
unsigned short			calculate_checksum(unsigned short *icmp, int len);
void					init_packet_memory(t_ping *ping);
void					setting_options(t_ping *ping);

#endif
