/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   including_struc.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:36:43 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:38:04 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDING_STRUC_H

# define INCLUDING_STRUC_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include "../lib/lib.h"
# include <sys/time.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_to_eat;
	struct timeval	tv;
	struct timeval	tv_init;
	pthread_mutex_t	*fork_tab;
	int				is_nb_to_eat;
	pthread_mutex_t	protect_death_value;
}	t_data;

typedef struct s_philof_info
{
	int			num;
	long int	last_eat_time;
	int			nb_eat;
	char		*philo_stat;
	int			is_philo_died;
}	t_philo_info;

typedef struct s_all
{
	t_philo_info	philo_info;
	t_data			data;
	int				*is_died;
}	t_all;

#endif