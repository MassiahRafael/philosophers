#include "philosophers.h"

void	free_table(t_table *table)
{
	unsigned int	i;	

	if (!table)
		return ;
	i = 0;
	if (table->fork)
		free(table->fork);
	if (table->forks_status)
		free(table->forks_status);
	if (table->phils_infos)
		free(table->phils_infos);
	free(table);
}
