# include "ft_ping.h"
#include "libft/libft.h"

void input_parsing(char **av, t_ping *ping)
{
	if (!av)
		error_handle(EXIT_FAILURE, "Invalid Parameters", ping);
	if (flag_validation(av, ping) == 1)
		error_handle(EXIT_FAILURE, "Invalid flag", ping);
	if (ip_validation(av, ping) == 1)
		error_handle(EXIT_FAILURE, "Invalid IP Schema", ping);
	printf("OPTION --------------> %s\n", ping->flag);
	// printf("IP ------------------> %s\n", ping->ip);
}

/*
	This function validates the Flag and checks if there is an empty arg
*/
int flag_validation(char **av, t_ping *ping)
{
	int counter;

	counter = 1;
	if (!av)
		error_handle(EXIT_FAILURE, "Invalid Parameters", ping);
	while (av[counter])
	{
		if (!*av[counter])
			return 1;
		if (ft_ispart(ping->flags_options, av[counter]) == 0)
		{
			ping->flag = ft_strdup(av[counter]);
			if (!ping->flag)
				error_handle(EXIT_FAILURE, "Error: Failed to allocate memory for flag", ping);
			return 0;
		}
		counter++;
	}
	return 1;
}

/*
*/
int ip_validation(char **av, t_ping *ping)
{
	int counter;

	counter = 1;
	if (!av)
		error_handle(EXIT_FAILURE, "Invalid Parameters", ping);
	while (av[counter])
	{
		if (!*av[counter])
			return 1;
		if (strcmp(ping->flag, av[counter]))
		{
			ping->dest_ip = ft_strdup(av[counter]);
			return 0;
		}
		counter++;
	}
	return 1;
}

// float elapsed_time = ((((stop.tv_sec - start.tv_sec) * 1000) + (stop.tv_usec - start.tv_usec)) / 1000);


// (((stop.tv_sec * 1000) + stop.tv_usec) - ((start.tv_sec * 1000) + start.tv_usec)/ 1000)