# include "ft_ping.h"
#include "libft/libft.h"


/*
This function sets up the environment to run the program.
*/
void setup(t_ping *ping)
{
	char *s[FLAG_OPTIONS_NUMBER + 1] = {"-v", "-?", NULL};

	ft_bzero(ping, sizeof(t_ping));
	ping->flags_options = ft_darray_copy(s);
	if (!ping->flags_options)
		error_handle(EXIT_FAILURE, "Error: Failed to copy flags options", ping);
}

/*
This function prints the usage of the program
*/
void print_usage()
{
	printf("Usage:\n");
    printf("  ./ft_ping [FLAG] [IP/DOMAIN]\n\n");
    printf("Flags:\n");
    printf("  -v ===> Verbose mode\n\n");
	printf("  -? ===> Help\n\n");
    printf("IP Format:\n");
    printf("  xxx.xxx.xxx.xxx\n");
	printf("DOMAIN Format:\n");
	printf("  www.example.com\n");
}

/*
The function prints %msg in %fd and exits incase of an error occurred.
*/
void error_handle(int status, char *msg, t_ping *ping)
{
	if (!msg)
		exit(EXIT_FAILURE);
	
	if (status == EXIT_FAILURE)
		fprintf(stderr, "%s\n", msg);
	
	// Clean up resources
	ft_darray_free(ping->flags_options);
	free(ping->flag);
	free(ping->dest_ip);
	
	exit(status);
}

float	get_minimum(t_ping *ping)
{
	if (!ping->timings || ping->index == 0)
		return 0;

	float min = ping->timings[0];
	for (int i = 1; i < ping->index; i++)
	{
		if (ping->timings[i] < min)
			min = ping->timings[i];
	}
	return min;
}

float	get_average(t_ping *ping)
{
	float avg = 0;
	for (int i = 0; i < ping->index; i++)
		avg += ping->timings[i];
	if (avg == 0)
		return (0);
	return (avg / ping->index);
}

float	get_maximum(t_ping *ping)
{
	if (!ping->timings || ping->index == 0)
		return 0;

	float max = ping->timings[0];
	for (int i = 1; i < ping->index; i++)
	{
		if (ping->timings[i] > max)
			max = ping->timings[i];
	}
	return max;
}

float	get_mdev(t_ping *ping)
{
	float mdev = 0;
	for (int i = 0; i < ping->index; i++)
		mdev += fabs(ping->timings[i] - get_average(ping));
	if (mdev == 0)
		return (0);
	return (mdev / ping->index);
}

char *convert_domain_to_ip(char *domain, t_ping *ping)
{
	struct hostent* h;
    h = gethostbyname(domain);
	char error_msg[256];
	if (!h)
	{
		snprintf(error_msg, sizeof(error_msg), "ft_ping: %s: Temporary failure in name resolution", domain);
		packet_failure(ping, error_msg);
	}
    return inet_ntoa(*(struct in_addr *)h->h_addr);
}

void flag_options_printing(t_ping *ping, int pid)
{
	if (ping->flag)
	{
		if (strcmp(ping->flag, "-v") == 0)
		{
			
			fprintf(stdout, "\nPING %s (%s): 56 data bytes, id 0x%x = %d\n", ping->dest_ip, ping->ip_rep, pid,pid);
		}
	}
	
}

int packet_reply_printing(int type, int recv_f, struct iphdr* ip_reply, int seq, float elapsed_time)
{
	struct in_addr src_addr;
	src_addr.s_addr = ip_reply->saddr;

	if (type == 3)
	{
		printf("Destination Unreachable\n");
		return 1;
	}
	else if (type == 5)
	{
		printf("Redirect\n");
		return 1;
	}
	else if (type == 11)
	{
		printf("%ld bytes from %s: Time to live exceeded\n",  recv_f - sizeof(struct iphdr), inet_ntoa(src_addr));
		return 1;
	}
	else if (type == 12)
	{
		printf("Parameter Problem\n");
		return 1;
	}
	else
	{
		printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms\n",  recv_f - sizeof(struct iphdr), inet_ntoa(src_addr), seq, ip_reply->ttl, elapsed_time);
		return 0;
	}
}