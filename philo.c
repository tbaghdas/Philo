
#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 0)
	{
		return (1);
	}
	data_init(&data);
	parsing_args(&data, argv);
	if (starting_simulation(&data) != 0)
	{
		return (1);
	}
	return (0);
}
