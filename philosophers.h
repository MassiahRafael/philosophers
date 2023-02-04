/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmassiah <rmassiah@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:25:32 by ade-sous          #+#    #+#             */
/*   Updated: 2023/02/04 17:37:59 by rmassiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_phil {
	int				id;
	int				dead;
	int				dinner_number;
	int				eating;
	time_t			last_dinner;
	int				fork_left;
	int				fork_right;
	t_table			*table;
	pthread_mutex_t	is_eating;
}	t_phil;

typedef struct s_table {
	int				phils_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_limit;
	long int		start;
	int				is_dead;
	int				satisfied;
	int				*forks_status;
	t_phil			*phils_infos;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printer;
	pthread_mutex_t	check_dead;
}	t_table;

t_table	*init_table(int argc, char **argv);
void	init_phils(t_table *table);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
int		is_number(char *str);
int		ft_check_input(int argc, char **argv);
void	print(char *situation, t_table *table, int phil_id);
void	eating(t_phil *phils);
void	sleeping(t_phil *phils);
void	thinking(t_phil *phils);
time_t	get_time(void);
time_t	diff_time(time_t start, time_t end);
void	set_fork_array(t_table *table);
void	take_forks(t_phil *phil);
int		finished(t_table *table);
void	check_time(t_table *table);
void	free_table(t_table *table);
int		waiter(t_table *table);
void	smart_sleep(long int us, t_table *table);
void	start_dinner(t_table *table, pthread_t *t);
int		ft_atoi(const char *str);
#endif
