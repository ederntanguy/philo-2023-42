/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_destroy.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:36:22 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:37:56 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREAT_DESTROY_H

# define CREAT_DESTROY_H

# include "philo.h"

pthread_mutex_t	*creat_protect_fork(t_data *all);
int				make_thread(t_data *data, t_philo_info *philo_info);
int				destroy_mutex(t_data *data);

#endif