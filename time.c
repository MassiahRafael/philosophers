/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmassiah <rmassiah@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:48 by rmassiah          #+#    #+#             */
/*   Updated: 2023/02/04 17:39:14 by rmassiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time(void)
{
	struct timeval	time;

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
	while ((get_time() - start) <= us)
	{
		if (table->is_dead == 1)
		{	
			break ;
		}
		usleep(100);
	}
	return ;
}
