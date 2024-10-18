/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:37:22 by etanguy           #+#    #+#             */
/*   Updated: 2023/04/13 10:37:30 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/other_action.h"

int	sleeping_action(t_all *all)
{
	if (show_action(all, "sleep") == 0)
		return (error(all));
	if (usleep(all->data.time_to_sleep) == -1)
		return (error(all));
	free(all->philo_info.philo_stat);
	all->philo_info.philo_stat = ft_strdup("thinking");
	if (all->philo_info.philo_stat == NULL)
		return (error(all));
	if (which_action(all) == 0)
		return (error(all));
	return (1);
}

int	thinking_action(t_all *all)
{
	if (show_action(all, "think") == 0)
		return (error(all));
	if (all->data.time_to_eat > all->data.time_to_sleep)
		usleep(all->data.time_to_eat - all->data.time_to_sleep);
	free(all->philo_info.philo_stat);
	all->philo_info.philo_stat = ft_strdup("eating");
	if (all->philo_info.philo_stat == NULL)
		return (error(all));
	if (which_action(all) == 0)
		return (error(all));
	return (1);
}
