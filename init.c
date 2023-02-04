/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmassiah <rmassiah@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:36:26 by rmassiah          #+#    #+#             */
/*   Updated: 2023/02/04 17:36:28 by rmassiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->start = 0;
	table->is_dead = 0;
	table->satisfied = 0;
	table->phils_number = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&table->check_dead, NULL);
	if (argc == 6)
		table->eat_limit = ft_atoi(argv[5]);
	else
		table->eat_limit = -1;
	return (table);
}

void	init_forks(t_phil *phil, t_table *table)
{
	phil->fork_left = phil->id - 1;
	if (phil->id != table->phils_number)
		phil->fork_right = phil->id;
	else
		phil->fork_right = 0;
}

void	init_phils(t_table *table)
{
	pthread_mutex_t	*fork;
	t_phil			*phils_infos;
	int				i;

	i = 0;
	phils_infos = malloc(sizeof(t_phil) * table->phils_number);
	fork = malloc(sizeof(pthread_mutex_t) * table->phils_number);
	while (i < table->phils_number)
	{
		pthread_mutex_init(&fork[i], NULL);
		pthread_mutex_init(&phils_infos[i].is_eating, NULL);
		phils_infos[i].table = table;
		phils_infos[i].id = i + 1;
		phils_infos[i].dead = 0;
		phils_infos[i].dinner_number = 0;
		init_forks(&phils_infos[i], table);
		i++;
	}
	table->fork = fork;
	table->phils_infos = phils_infos;
}

void	set_fork_array(t_table *table)
{
	int	i;
	int	*fork_array;

	i = 0;
	fork_array = malloc(sizeof(int) * table->phils_number);
	while (i < table->phils_number)
	{
		fork_array[i] = 1;
		i++;
	}
	table->forks_status = fork_array;
}
