#include "philosophers.h"

void	*thread_func(void *routine)
{
	t_phil	*phils;

	phils = (t_phil *)routine;
	if (phils->id % 2 == 0)
		usleep(200);
	while (!finished(phils->table))
	{
		take_forks(phils);
		if (&phils->table->fork[phils->fork_left]
			== &phils->table->fork[phils->fork_right])
			return (NULL);
		sleeping(phils);
		thinking(phils);
	}
	return (NULL);
}

void	start_dinner(t_table *table, pthread_t *t)
{
	int	i;
	int	s;

	i = 0;
	while (i < table->phils_number)
	{
		table->phils_infos[i].last_dinner = table->start;
		s = pthread_create(&t[i], NULL, thread_func, &table->phils_infos[i]);
		i++;
	}
	i = 0;
	waiter(table);
	while (i < table->phils_number)
	{
		s = pthread_join(t[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_t	*t;
	t_table		*table;

	if (!ft_check_input(argc, argv))
	{
		table = init_table(argc, argv);
		set_fork_array(table);
		pthread_mutex_init(&table->printer, NULL);
		init_phils(table);
		t = malloc(sizeof(pthread_t) * table->phils_number);
		table->start = get_time();
		start_dinner(table, t);
		free(t);
		free_table(table);
	}
	return (0);
}
