/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:36:14 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:36:19 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/action.h"

long int	get_time(t_all *all)
{
	time_t		seconds;
	suseconds_t	microseconds;

	if (gettimeofday(&(all->data.tv), NULL) == -1)
		return (-1);
	seconds = all->data.tv.tv_sec - all->data.tv_init.tv_sec;
	microseconds = all->data.tv.tv_usec - all->data.tv_init.tv_usec;
	return (seconds * 1000 + microseconds / 1000);
}

int	show_action(t_all *all, char *action)
{
	long int		miliseconds;

	miliseconds = get_time(all);
	if (miliseconds == -1)
		return (0);
	if (ft_strcmp(action, "take"))
		protect_printf("has taken a fork\n", miliseconds, all);
	else if (ft_strcmp(action, "eat"))
	{
		protect_printf("is eating\n", miliseconds, all);
		all->philo_info.nb_eat++;
		all->philo_info.last_eat_time = miliseconds;
	}
	else if (ft_strcmp(action, "sleep"))
		protect_printf("is sleeping\n", miliseconds, all);
	else if (ft_strcmp(action, "think"))
		protect_printf("is thinking\n", miliseconds, all);
	else if (ft_strcmp(action, "died"))
	{
		protect_printf("died\n", miliseconds, all);
		protect_is_died(all);
		all->philo_info.is_philo_died = 1;
	}
	return (1);
}

static int	which_action2(t_all *all)
{
	if (ft_strcmp(all->philo_info.philo_stat, "thinking"))
	{
		if (thinking_action(all) == 0)
			return (error(all));
	}
	else if (ft_strcmp(all->philo_info.philo_stat, "eating"))
	{
		if (eating_action(all) == 0)
			return (error(all));
	}
	else if (ft_strcmp(all->philo_info.philo_stat, "sleeping"))
	{
		if (sleeping_action(all) == 0)
			return (error(all));
	}
	return (1);
}

int	which_action(t_all *all)
{
	int	tmp;

	pthread_mutex_lock(is_died_lock());
	if ((*(all->is_died)) == 1 || (all->data.nb_to_eat >= 0
			&& all->philo_info.nb_eat == all->data.nb_to_eat))
		return (pthread_mutex_unlock(is_died_lock()), 1);
	pthread_mutex_unlock(is_died_lock());
	tmp = get_time(all);
	if (tmp == -1)
		return (error(all));
	if (tmp - all->philo_info.last_eat_time > all->data.time_to_die / 1000)
	{
		if (all->philo_info.is_philo_died == 0 && show_action(all, "died") == 0)
			return (error(all));
	}
	else if (ft_strcmp(all->philo_info.philo_stat, "thinking")
		|| ft_strcmp(all->philo_info.philo_stat, "eating")
		|| ft_strcmp(all->philo_info.philo_stat, "sleeping"))
	{
		if (which_action2(all) == 0)
			return (error(all));
	}
	return (1);
}

void	*action(void *to_send)
{
	t_all	*all2;

	all2 = (t_all *) to_send;
	if (which_action(all2) == 0)
		ft_putstr_fd("Error\n", 2);
	if (all2->philo_info.philo_stat)
		free(all2->philo_info.philo_stat);
	return (NULL);
}
