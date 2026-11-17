/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 18:45:22 by elsouza           #+#    #+#             */
/*   Updated: 2026/08/27 01:11:33 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	size = ft_strlen(s) - (size_t)start;
	if (len < size)
		size = len;
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
