/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 20:05:10 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/16 17:58:13 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	read_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static void	free_split(char **word)
{
	int	i;

	i = 0;
	while (word[i])
		free(word[i++]);
	free(word);
}

static int	parse_arg(char *arg, t_stack *a)
{
	char	**words;
	int		is_ok;
	int		i;
	int		n;

	n = 0;
	words = ft_split(arg, ' ');
	if (!words)
		return (0);
	is_ok = (words[0] != NULL);
	i = 0;
	while (words[i] && is_ok)
		is_ok = (parse_number(words[i++], &n) && !has_value(a, n)
				&& add_bottom(a, n));
	free_split(words);
	return (is_ok);
}

int	parse_number(char *str, int *out)
{
	int		i;
	int		sign;
	long	result;
	long	limit;

	i = 0;
	result = 0;
	sign = read_sign(str, &i);
	limit = INT_MAX;
	if (sign == -1)
		limit = INT_MAX + 1L;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > limit)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	*out = (int)(result * sign);
	return (1);
}

int	parse_args(char **argv, int start, t_stack *a)
{
	int	i;
	int	n;

	i = start;
	while (argv[i])
	{
		n = parse_arg(argv[i++], a);
		if (!n)
			return (0);
	}
	return (1);
}
