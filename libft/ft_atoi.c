/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 16:21:19 by elsouza           #+#    #+#             */
/*   Updated: 2026/10/11 09:25:30 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		neg;
	int		val;

	i = 0;
	while (nptr[i] && is_sep(nptr[i]))
		i++;
	neg = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	val = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		val = val * 10 + (nptr[i] - '0');
		i++;
	}
	return (val * neg);
}
