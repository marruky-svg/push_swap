/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:06:29 by elsouza           #+#    #+#             */
/*   Updated: 2026/08/27 01:00:12 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		words;
	size_t	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && !(s[i] == c))
		{
			words++;
			while (s[i] && !(s[i] == c))
				i++;
		}
	}
	return (words);
}

static char	**free_memory(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static int	fill_word(char **arr, char const *s, size_t *i, char c)
{
	unsigned int	start;

	start = (unsigned int)*i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	*arr = ft_substr(s, start, *i - start);
	return ((*arr != NULL));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;

	arr = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		if (!fill_word(&arr[j], s, &i, c))
			return (free_memory(arr, j));
		j++;
	}
	arr[j] = NULL;
	return (arr);
}
