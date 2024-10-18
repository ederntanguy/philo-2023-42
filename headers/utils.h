/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:38:14 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:38:17 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include "philo.h"

int				error(t_all *all);
pthread_mutex_t	*is_died_lock(void);
pthread_mutex_t	*printf_lock(void);
void			protect_is_died(t_all *all);
void			protect_printf(char *str, long int milisiconds, t_all *all);

#endif
