/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:13:54 by elsouza           #+#    #+#             */
/*   Updated: 2026/08/27 02:17:35 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*chr;

	chr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			chr = (char *)s;
		s++;
	}
	if (*s == (char)c)
		chr = (char *)s;
	return (chr);
}
