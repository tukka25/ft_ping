#include "ft_ping.h"

int main(int ac, char **av)
{
	t_ping ping;

	if (ac >= 2 && ac <= 3)
	{
		setup(&ping);
		input_parsing(av, &ping);
		packet_send(&ping);
		return (0);
	}
	print_usage();
	return (1);
}