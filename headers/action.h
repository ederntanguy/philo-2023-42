/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:36:17 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:37:56 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H

# define ACTION_H

# include "philo.h"

int				show_action(t_all *all, char *action);
void			*action(void *all);
int				which_action(t_all *all);
long int		get_time(t_all *all);

#endif
