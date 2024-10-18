/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:36:19 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:36:36 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/creat_destroy.h"

pthread_mutex_t	*creat_protect_fork(t_data *data)
{
	pthread_mutex_t	*fork_tab;
	int				i;

	i = 0;
	fork_tab = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!fork_tab)
		return (NULL);
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&(fork_tab[i++]), NULL) != 0)
			return (NULL);
	}
	return (fork_tab);
}

int	creat_and_execute_threads(t_all *all, pthread_t	*philo_tab, t_data *data)
{
	int	i;

	i = 0;
	while (data->number_of_philosophers > i)
	{
		if (pthread_create(&(philo_tab[i]), NULL, action, &(all[i])) != 0)
			return (free(all), free(philo_tab),
				ft_putstr_fd("Can't Creat Thread\n", 2), 0);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philo_tab[i++], NULL) != 0)
			return (free(all), free(philo_tab), 0);
	}
	return (1);
}

int	make_thread(t_data *data, t_philo_info *philo_info)
{
	int			i;
	pthread_t	*philo_tab;
	t_all		*all;
	int			is_died;

	is_died = 0;
	all = malloc(sizeof(t_all) * data->number_of_philosophers);
	if (!all)
		return (0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		all[i].data = *data;
		all[i].philo_info = philo_info[i];
		all[i].is_died = &is_died;
		i++;
	}
	philo_tab = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!philo_tab)
		return (free(all), 0);
	if (creat_and_execute_threads(all, philo_tab, data) == 0)
		return (0);
	return (free(all), free(philo_tab), 1);
}

int	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&(data->fork_tab[i++])) != 0)
			return (0);
	}
	if (pthread_mutex_destroy(printf_lock()) != 0)
		return (0);
	if (pthread_mutex_destroy(is_died_lock()) != 0)
		return (0);
	return (1);
}
