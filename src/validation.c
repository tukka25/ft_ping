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