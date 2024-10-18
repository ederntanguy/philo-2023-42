/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:01:33 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:36:54 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/eating_part.h"

static int	check_solo_eating(t_all *all)
{
	if (all->data.number_of_philosophers == 1)
	{
		if (show_action(all, "take") == 0)
			return (error(all));
		while (get_time(all) - all->philo_info.last_eat_time
			< all->data.time_to_die / 1000)
			continue ;
		if (show_action(all, "died") == 0)
			return (error(all));
		return (1);
	}
	return (2);
}

static int	check_died_between_take_fork(t_all *all)
{
	if (all->philo_info.num + 1 == all->data.number_of_philosophers)
		pthread_mutex_lock(&(all->data.fork_tab[(all->philo_info.num + 1)
				% all->data.number_of_philosophers]));
	else
		pthread_mutex_lock(&(all->data.fork_tab[all->philo_info.num]));
	if (get_time(all) - all->philo_info.last_eat_time
		> all->data.time_to_die / 1000)
	{
		if (all->philo_info.num + 1 == all->data.number_of_philosophers)
			pthread_mutex_unlock(&(all->data.fork_tab[(all->philo_info.num + 1)
					% all->data.number_of_philosophers]));
		else
			pthread_mutex_unlock(&(all->data.fork_tab[all->philo_info.num]));
		if (all->philo_info.is_philo_died == 0 && show_action(all, "died") == 0)
			return (error(all));
		return (2);
	}
	return (1);
}

static int	end_eating_action(t_all *all)
{
	if (show_action(all, "take") == 0)
		return (error(all));
	if (show_action(all, "eat") == 0)
		return (error(all));
	usleep(all->data.time_to_eat);
	if (pthread_mutex_unlock(&(all->data.fork_tab[all->philo_info.num])) != 0)
		return (error(all));
	if (pthread_mutex_unlock(&(all->data.fork_tab[(all->philo_info.num + 1)
					% all->data.number_of_philosophers])) != 0)
		return (error(all));
	free(all->philo_info.philo_stat);
	all->philo_info.philo_stat = ft_strdup("sleeping");
	if (all->philo_info.philo_stat == NULL)
		return (error(all));
	if (which_action(all) == 0)
		return (error(all));
	return (1);
}

static int	died_check(t_all *all)
{
	pthread_mutex_lock(is_died_lock());
	if (all->philo_info.is_philo_died == 0 && (*(all->is_died)) == 1)
		return (pthread_mutex_unlock(is_died_lock()), 1);
	pthread_mutex_unlock(is_died_lock());
	return (1);
}

int	eating_action(t_all *all)
{
	int	tmp;

	if (check_solo_eating(all) == 0)
		return (error(all));
	if (all->philo_info.is_philo_died == 1)
		return (1);
	tmp = check_died_between_take_fork(all);
	if (tmp == 0)
		return (error(all));
	else if (tmp == 2)
		return (1);
	if (show_action(all, "take") == 0)
		return (error(all));
	if (all->philo_info.num + 1 == all->data.number_of_philosophers)
		pthread_mutex_lock(&(all->data.fork_tab[all->philo_info.num]));
	else
		pthread_mutex_lock(&(all->data.fork_tab[(all->philo_info.num + 1)
				% all->data.number_of_philosophers]));
	if (end_eating_action(all) == 0)
		return (error(all));
	died_check(all);
	return (1);
}
