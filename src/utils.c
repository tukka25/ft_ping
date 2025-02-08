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
void error_handle(int fd, char *msg)
{
	if (!msg)
		exit(1);
	printf("%s\n", msg);
	exit(1);
}