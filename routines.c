/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmassiah <rmassiah@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:31 by rmassiah          #+#    #+#             */
/*   Updated: 2023/02/04 17:38:34 by rmassiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_phil *phils)
{
	print("sleep", phils->table, phils->id);
	smart_sleep(phils->table->time_to_sleep, phils->table);
}

void	thinking(t_phil *phils)
{
	if (phils->table->is_dead == 1)
		return ;
	print("thinking", phils->table, phils->id);
}

void	take_forks(t_phil *phil)
{
	int	*left_status;
	int	*right_status;

	pthread_mutex_lock(&phil->table->fork[phil->fork_left]);
	left_status = &phil->table->forks_status[phil->fork_left];
	if (*left_status == 1)
	{
		*left_status = 0;
		print("fork0", phil->table, phil->id);
	}
	else
		pthread_mutex_unlock(&phil->table->fork[phil->fork_left]);
	if (&phil->table->fork[phil->fork_left]
		== &phil->table->fork[phil->fork_right])
		return ;
	pthread_mutex_lock(&phil->table->fork[phil->fork_right]);
	right_status = &phil->table->forks_status[phil->fork_right];
	if (*right_status == 1)
	{
		*right_status = 0;
		print("fork1", phil->table, phil->id);
	}
	else
		pthread_mutex_unlock(&phil->table->fork[phil->fork_right]);
	eating(phil);
}

void	eating(t_phil *phil)
{
	int	*left_status;
	int	*right_status;

	left_status = &phil->table->forks_status[phil->fork_left];
	right_status = &phil->table->forks_status[phil->fork_right];
	if (*left_status == 0 && *right_status == 0)
	{
		pthread_mutex_lock(&phil->is_eating);
		print("eat", phil->table, phil->id);
		phil->last_dinner = get_time();
		smart_sleep(phil->table->time_to_eat, phil->table);
		phil->dinner_number += 1;
		*right_status = 1;
		*left_status = 1;
		pthread_mutex_unlock(&phil->table->fork[phil->fork_left]);
		pthread_mutex_unlock(&phil->table->fork[phil->fork_right]);
		pthread_mutex_unlock(&phil->is_eating);
		if (phil->dinner_number == phil->table->eat_limit)
			phil->table->satisfied += 1;
	}
}
