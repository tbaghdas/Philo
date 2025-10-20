

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>//??
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					eaten;
	size_t				last_time_ate;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;

}						t_philo;

typedef struct s_data
{
	int					philo_count;
	int					eat_count;
	int					done;
	int					full;
	int					died;
	int					time_to_eat;
	int					time_to_sleep;
	size_t				time_to_die;
	long				start;
	pthread_mutex_t		mutex_for_check_meal;
	pthread_mutex_t		mutex_for_eat;
	pthread_mutex_t		mutex_for_died;
	pthread_mutex_t		mutex_for_print;
	pthread_t			monitor;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_data;

int						check_args(int argc, char **argv);
void					parsing_args(t_data *data, char **argv);
int						ft_atoi(const char *str);
void					data_init(t_data *data);
int						philos_init(t_data *data);
int						create_philos(t_data *data);
int						create_forks(t_data *data);
void					join(t_data *data);
int						starting_simulation(t_data *data);
void					*philo_routine(void *arg);
size_t					time_now(void);
void					printf_time(t_philo *philo, char *str, char *color);
void					*monitoring_loop(void *arg);
void					destroy(t_data *data);
void					sleeping(size_t time, t_philo *philo);
void					eat(t_philo *philo);
void					main_loop(t_philo *philo);
int						check_life(t_data *data);
int						done_eating(t_data *data);
int						overflow_check(char *str);

#endif