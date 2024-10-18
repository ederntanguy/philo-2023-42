/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etanguy <etanguy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:07:20 by etanguy           #+#    #+#             */
/*   Updated: 2022/11/09 14:48:05 by etanguy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*creat;
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(s);
	creat = malloc((i + 1) * sizeof(char));
	if (!creat)
		return (NULL);
	while (i > j)
	{
		creat[j] = s[j];
		j++;
	}
	creat[j] = '\0';
	return (creat);
}
