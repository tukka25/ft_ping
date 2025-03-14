# include "ft_ping.h"
#include "libft/libft.h"


/*
This function sets up the environment to run the program.
*/
void setup(t_ping *ping)
{
	char *s[FLAG_OPTIONS_NUMBER + 1] = {"-v", NULL};

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
    printf("  ./ft_ping [FLAG] [IP]\n\n");
    printf("Flags:\n");
    printf("  -v ===> Verbose mode\n\n");
    printf("IP Format:\n");
    printf("  xxx.xxx.xxx.xxx\n");
}

/*
The function prints %msg in %fd and exits incase of an error occurred.
*/
void error_handle(int fd, char *msg, t_ping *ping)
{
	if (!msg)
		exit(1);
	printf("%s\n", msg);
	ft_darray_free(ping->flags_options);
	exit(fd);
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

char *convert_domain_to_ip(char *domain, t_ping *ping)
{
	struct hostent* h;
    h = gethostbyname(domain);
	char error_msg[256];
	snprintf(error_msg, sizeof(error_msg), "ft_ping: %s: Temporary failure in name resolution", domain);
	if (!h)
		error_handle(1, error_msg, ping);
    return inet_ntoa(*(struct in_addr *)h->h_addr);
}