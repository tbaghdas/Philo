

#include "philo.h"

void	parsing_args(t_data *data, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat_count = ft_atoi(argv[5]);
	else
		data->eat_count = -1;
}

int	overflow_check(char *str)
{
	int		sign;
	long	result;
	int		i;

	sign = 1;
	result = 0;
	i = 1;
	if (str[0] == '-')
	{
		sign = -1;
	}
	while (str[i] != '\0')
	{
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > 2147483647)
		{
			return (1);
		}
		if (sign == -1 && (-result) < -2147483648)
		{
			return (1);
		}
		i++;
	}
	return (1);
}

static int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != '-' || i != 0))
		{
			return (1);
		}
		i++;
	}
	return (1);
}

static int	check_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		return (1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (check_count(argc) != 0)
	{
		printf("Error: Wrong number of arguments\n");
		printf("Usage: ./philo count_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [eat_count]\n");
		return (1);
	}
	while (argv[i])
	{
		if (check_digit(argv[i]) != 0)
		{
			printf("Error: The arguments must be numbers!\n");
			return (1);
		}
		if (overflow_check(argv[i]) != 0)
		{
			printf("Error: The numbers must be in range of int!\n");
			return (1);
		}
		i++;
	}
	return (0);
}
