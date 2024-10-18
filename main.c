/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:37:08 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:37:00 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo.h"

__attribute__((__constructor__()))
void	printf_lock_init(void)
{
	pthread_mutex_init(is_died_lock(), NULL);
	pthread_mutex_init(printf_lock(), NULL);
}

int	init_var(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (gettimeofday(&(data->tv_init), NULL) != 0)
		return (0);
	if (argc == 6)
	{
		data->is_nb_to_eat = 1;
		data->nb_to_eat = ft_atoi(argv[5]);
	}
	else
	{
		data->is_nb_to_eat = 0;
		data->nb_to_eat = -1;
	}
	return (1);
}

static int	loop_init_philo(t_data *d, t_philo_info **phil, int i, int phil_ev)
{
	while (i < d->number_of_philosophers)
	{
		(*phil)[i].num = i;
		(*phil)[i].last_eat_time = 0;
		(*phil)[i].nb_eat = 0;
		(*phil)[i].is_philo_died = 0;
		if (i % 2 == 0)
			(*phil)[i].philo_stat = ft_strdup("eating");
		else
			(*phil)[i].philo_stat = ft_strdup("sleeping");
		if (!(*phil)[i].philo_stat)
			return (0);
		if (i == d->number_of_philosophers - 1 && phil_ev == 0)
		{
			free((*phil)[i].philo_stat);
			(*phil)[i].philo_stat = ft_strdup("thinking");
			if (!(*phil)[i].philo_stat)
				return (0);
		}
		i++;
	}
	return (1);
}

int	init_philo(t_data *data, t_philo_info **philo_info)
{
	int	i;
	int	is_philo_even;

	i = 0;
	*philo_info = malloc(sizeof(t_philo_info) * data->number_of_philosophers);
	if (!(*philo_info))
		return (0);
	if (data->number_of_philosophers % 2 == 0)
		is_philo_even = 1;
	else
		is_philo_even = 0;
	if (!loop_init_philo(data, philo_info, i, is_philo_even))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo_info	*philo_info;

	if (!(argc >= 5 && argc <= 6))
		return (ft_putstr_fd("Invalid Arguments\n", 2), 1);
	if (init_var(&data, argc, argv) == 0)
		return (ft_putstr_fd("Error\n", 2), 1);
	if (data.number_of_philosophers <= 0
		|| (data.is_nb_to_eat && data.nb_to_eat <= 0) || data.time_to_sleep <= 0
		|| data.time_to_eat <= 0 || data.time_to_die <= 0)
		return (ft_putstr_fd("Invalid Arguments\n", 2), 1);
	is_died_lock();
	if (init_philo(&data, &philo_info) == 0)
		return (ft_putstr_fd("Error\n", 2), 1);
	data.fork_tab = creat_protect_fork(&data);
	if (!data.fork_tab)
		return (ft_putstr_fd("Error\n", 2), 1);
	if (make_thread(&data, philo_info) == 0)
		return (ft_putstr_fd("Error\n", 2), 1);
	if (destroy_mutex(&data) == 0)
		return (ft_putstr_fd("Error\n", 2), 1);
	return (free(philo_info), free(data.fork_tab), 0);
}
