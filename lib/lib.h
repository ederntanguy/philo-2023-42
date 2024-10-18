/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:14:16 by etanguy           #+#    #+#             */
/*   Updated: 2022/11/13 16:36:06 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB

# define LIB

# include <unistd.h>

int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif