#include "philosophers.h"

void	print(char *situation, t_table *table, int phil_id)
{
	pthread_mutex_lock(&table->printer);
	if (finished(table))
	{
		pthread_mutex_unlock(&table->printer);
		return ;
	}
	printf("%ld ", diff_time(table->start, get_time()));
	if (!ft_strcmp(situation, "fork0"))
		printf("%d has taken a fork (left)\n", phil_id);
	else if (!ft_strcmp(situation, "fork1"))
		printf("%d has taken a fork (right)\n", phil_id);
	else if (!ft_strcmp(situation, "eat"))
		printf("%d is eating\n", phil_id);
	else if (!ft_strcmp(situation, "sleep"))
		printf("%d is sleeping\n", phil_id);
	else
		printf("%d is thinking\n", phil_id);
	pthread_mutex_unlock(&table->printer);
}

time_t	get_time(void)
{
	struct timeval	time;// 1 s -> 1000 ms ->1000000 us
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

time_t	diff_time(time_t start, time_t end)
{
	return (end - start);
}

void	smart_sleep(long int us, t_table *table)
{
	long int	start;

	start = get_time();
	while (table->is_dead == 0)
	{
		// printf("get_time - start : %ld | us : %ld\n", get_time() - start, us);
		if ((get_time() - start) * 1000 >= us)
			break ;
		usleep(100);
	}
	return ;
}
/*
	if(get_time() - phil->last_dinner > table->time_to_dead)
		table->is_dead = 1;
*/

int	finished(t_table *table)
{
	if (table->is_dead == 1)
		return (1);
	if (table->satisfied == table->phils_number)
		return (1);
	return (0);
}

int	waiter(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->phils_number)
		{
			//pthread_mutex_lock (&table->phils_infos[i].is_eating);
			//printf("%d --> %d last_dinner: %ld ms atrás (%ld)| time_to_die: %d ms\n", get_time() - table->start ,i + 1, (get_time() - table	->phils_infos[i].last_dinner), table->phils_infos[i].last_dinner, table->time_to_die);
			if ((get_time() - table->phils_infos[i].last_dinner) > table->time_to_die)
			{
				table->is_dead = 1;
				printf ("%ld %d dead\n", diff_time(table->start, get_time()),i + 1);
				pthread_mutex_unlock (&table->phils_infos[i].is_eating);
				//printf("saiu do garçom, deead\n");
				return (1);
			}
			if (table->satisfied == table->phils_number)
			{
				pthread_mutex_unlock (&table->phils_infos[i].is_eating);
				return (1);
			}
			//pthread_mutex_unlock(&table->phils_infos[i].is_eating);
			//printf("is_dead: %d\n", table->is_dead);
			i++;
		}
	}
}
