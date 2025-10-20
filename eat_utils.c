
#include "philo.h"

void	eat(t_philo *philo)
{
	printf_time(philo, "is eating", GREEN);
	pthread_mutex_lock(&philo->data->mutex_for_check_meal);
	philo->last_time_ate = time_now();//or after??
	pthread_mutex_unlock(&philo->data->mutex_for_check_meal);
	sleeping(philo->data->time_to_eat, philo);
	if (philo->data->eat_count != -1)
	{
		pthread_mutex_lock(&philo->data->mutex_for_eat);
		philo->eaten++;
		if (philo->eaten == philo->data->eat_count)
			philo->data->full++;
		pthread_mutex_unlock(&philo->data->mutex_for_eat);
	}
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf_time(philo, "has taken a fork", WHITE);
		pthread_mutex_lock(philo->right_fork);
		printf_time(philo, "has taken a fork", WHITE);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf_time(philo, "has taken a fork", WHITE);
		pthread_mutex_lock(philo->left_fork);
		printf_time(philo, "has taken a fork", WHITE);
	}
}

static void	leave_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	main_loop(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_for_died);
		if (philo->data->died || philo->data->done)
		{
			pthread_mutex_unlock(&philo->data->mutex_for_died);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_for_died);
		take_forks(philo);
		eat(philo);
		leave_forks(philo);
		printf_time(philo, "is sleeping", CYAN);
		sleeping(philo->data->time_to_sleep, philo);
		printf_time(philo, "is thinking", YELLOW);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf_time(philo, "has taken a fork", WHITE);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		usleep(1000);
	}
	main_loop(philo);
	return (NULL);
}
