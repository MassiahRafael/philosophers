#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_phil { //informações dos filósofos
	int				id;
	int				dead;       //se já morreu ou não
	int				dinner_number;      //quantas vezes já comeu
	int				eating;            //se está comendo
	time_t			last_dinner;
	int				fork_left;
	int				fork_right;
	t_table			*table;
	pthread_mutex_t	is_eating;
}	t_phil;

typedef struct s_table {
	int				phils_number;     //número de filosofos
	int				time_to_die;       //tempo de morte ao ficar sem comer
	int				time_to_eat;       //tempo gasto comendo
	int				time_to_sleep;     //tempo gasto dormindo
	int				eat_limit;		   //limite de vezes que precisa comer
	long int		start;			   //início do programa
	int				is_dead;
	int				satisfied;		   //número de phils satisfeitos
	int				*forks_status;     //para saber garfos disponíveis
	t_phil			*phils_infos;      //struct de cada filósofo
	pthread_mutex_t	dinner_mutex;          //controlar a impressão
	pthread_mutex_t	*fork;             //garfos (mutex)
	pthread_mutex_t	printer;          //controlar a impressão
	pthread_mutex_t	check_dead;          //controlar a morte
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

//obs.: fazer um mutex para não analisar se morreu com o filósofo comendo, pois se elee stá comendo, está vivo.
#endif
