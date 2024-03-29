/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmassiah <rmassiah@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:32:51 by rmassiah          #+#    #+#             */
/*   Updated: 2023/02/04 17:33:09 by rmassiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_table(t_table *table)
{
	if (!table)
		return ;
	if (table->fork)
		free(table->fork);
	if (table->forks_status)
		free(table->forks_status);
	if (table->phils_infos)
		free(table->phils_infos);
	free(table);
}
