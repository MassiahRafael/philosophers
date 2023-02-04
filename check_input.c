/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmassiah <rmassiah@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:35:39 by rmassiah          #+#    #+#             */
/*   Updated: 2023/02/04 17:35:53 by rmassiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_number(char *num)
{
	int	count;

	count = 0;
	if (num[count] == '+' && ft_isdigit(num[count + 1]))
		count++;
	while (num[count] && ft_isdigit(num[count]))
		count++;
	if (num[count] != '\0' && !ft_isdigit(num[count]))
		return (0);
	return (1);
}

int	ft_check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("correct input: ./philo number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat].\n");
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0 || !is_number(argv[i]))
		{
			printf("Use only positive numbers\ncorrect input: ./philo number_of_philosophers time_to_die\
 time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat].\n");
			return (1);
		}
		i++;
	}
	return (0);
}
