/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:37:06 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:37:19 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/utils.h"

int	error(t_all *all)
{
	pthread_mutex_lock(is_died_lock());
	(*(all->is_died)) = 1;
	pthread_mutex_unlock(is_died_lock());
	return (0);
}

pthread_mutex_t	*printf_lock(void)
{
	static pthread_mutex_t	protect_printf;

	return (&protect_printf);
}

pthread_mutex_t	*is_died_lock(void)
{
	static pthread_mutex_t	protect_is_died;

	return (&protect_is_died);
}

void	protect_printf(char *str, long int milisiconds, t_all *all)
{
	pthread_mutex_lock(printf_lock());
	printf("%ld %d %s", milisiconds, all->philo_info.num + 1, str);
	pthread_mutex_unlock(printf_lock());
}

void	protect_is_died(t_all *all)
{
	pthread_mutex_lock(is_died_lock());
	(*(all->is_died)) = 1;
	pthread_mutex_unlock(is_died_lock());
}
