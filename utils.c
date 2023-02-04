/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmassiah <rmassiah@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:39:23 by rmassiah          #+#    #+#             */
/*   Updated: 2023/02/04 17:39:28 by rmassiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("%d has taken a fork\n", phil_id);
	else if (!ft_strcmp(situation, "fork1"))
		printf("%d has taken a fork\n", phil_id);
	else if (!ft_strcmp(situation, "eat"))
		printf("%d is eating\n", phil_id);
	else if (!ft_strcmp(situation, "sleep"))
		printf("%d is sleeping\n", phil_id);
	else
		printf("%d is thinking\n", phil_id);
	pthread_mutex_unlock(&table->printer);
}

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
		i = -1;
		while (++i < table->phils_number)
		{
			if ((get_time() - table->phils_infos[i].last_dinner)
				> table->time_to_die)
			{
				pthread_mutex_lock(&table->printer);
				table->is_dead = 1;
				printf ("%ld %d dead\n", diff_time(table->start, get_time()),
					i + 1);
				pthread_mutex_unlock(&table->printer);
				pthread_mutex_unlock (&table->phils_infos[i].is_eating);
				return (1);
			}
			if (table->satisfied == table->phils_number)
			{
				pthread_mutex_unlock (&table->phils_infos[i].is_eating);
				return (1);
			}
		}
	}
}
