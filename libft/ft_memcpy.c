/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 20:35:29 by elsouza           #+#    #+#             */
/*   Updated: 2026/10/30 01:01:42 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				size;

	if (!n)
		return (dst);
	if (!dst && !src)
		return (NULL);
	size = 0;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (size < n)
	{
		d[size] = s[size];
		size++;
	}
	return (dst);
}

/*
#include "stdio.h"
int main()
{
	char dst[] = "efnaopfgneiobg.   ianegnag";
	const char *src = "elder corre";
	ft_memcpy(dst, src, 5);
	printf("%s", dst);
}
*/